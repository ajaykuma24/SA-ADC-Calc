#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <stdlib.h>  
using namespace std;
char choose ();
double nums(bool);
int main()
{
	char repeat; //input result to repeat program
	do	//loop to repeat program
	{
		double Vref;	//Vref
		int bits;	//# of bits
		int binwidth;	//setwidth value for binary in table
		double vol;	//voltage to evaluate to in binary
		double ss;	//step size
		unsigned int dec = 0;	//decimal value of binary
		double tryvol;	//resulting voltage from binary value times step size
		double error;	//error percentage
		bool quit = 0;	//input information is correct
		bool doubl = 1;	//value passed to function if result should be a double
		char cor = 'y';	//input when information is correct
		
		cout << "Welcome to the SA ADC Calculator :)" << endl;//beginning text
		do//loop if information is incorrect
		{
			cout << "Enter Vref: ";//vref input
			Vref = nums(doubl);	//function returns valid double
			while (Vref<=0)//if vref is 0
			{
				cout <<"Voltage must be greater than 0. Enter new value: ";
				Vref = nums(doubl);
			}
			doubl = 0;//bits should not have decimal point
			cout << "Enter number of bits: ";//input bits
			bits = nums(doubl);//function returns valid int
			while (bits > 32)//bits^2 is too large
			{
				cout <<"Value too large. Please enter value of 32 or less: ";
				bits = nums(doubl);
			}
			while (bits<=0)//if bits = 0
			{
				cout <<"Value too small. Please enter value greater than 0: ";
				bits = nums(doubl);
			}
			doubl = 1;//analog voltage can be a double
			cout << "Enter Analog Voltage: ";//enter analog voltage
			vol = nums(doubl);//get vaid double number
			while (vol>Vref||vol<=0)//if voltage is greater than vref or = 0
			{
				if(vol>Vref)
				cout <<"Error. Voltage greater than Vref. Enter new value: ";
				else cout <<"Error. Voltage must be greater than 0. Enter new value: ";
				vol = nums(doubl);
			}
			cout << "Is this information correct?"<<endl;//ask if info correct
			//table for info
			cout << setw(8)<<"Vref"<<setw(13)<<"# of bits"<<setw(18)<<"Analog Voltage"<<endl;
			cout << setfill('_')<<setw(8)<<""<<"    "<<setfill('_')<<setw(9)<<""<<"    "<<setfill('_')<<setw(14)<<""<<endl;
			cout << setfill(' ')<<setw(8)<<Vref<<setw(13)<<bits<<setw(18)<<vol<<endl;
			cout<<" Type 'y' for yes or 'n' for no:";
			cor = choose();//get valid yes or no
		}while (cor == 'n');//if cor = n
		ss = Vref/pow(2,bits);//step size
		int bin[bits];//int array for binary value
		for(int i = 0; i<bits; ++i)//set it to 0
			bin[i] = 0;
		bin[0] = 1;//first value starts at 1
		cout<<endl;
		if(bits<13)//for binary formatting
			binwidth = (12-bits)+bits;
		else binwidth = bits;//for binary formatting
		cout<<setw(10)<<"Voltage"<<setw(binwidth+4)<<"Binary Value"<<setw(8)<<"Step"<<endl;//table for steps
		cout << setfill('_')<<setw(10)<<""<<"    "<<setfill('_')<<setw(binwidth)<<""<<"    "<<setfill('_')<<setw(4)<<""<<endl;
		if(bits<13)//for binary formatting
			binwidth+=1;
		for (int i = 0; i<bits&&!quit; ++i)//while going through binary value, or if voltage is equal to input
		{
			tryvol = 0;//trial voltage to test
			unsigned int val = pow(2,(bits-1));//msb of binary vaule in decimal
			dec=0;//decimal value of binary value
			for(int j = 0; j<bits;++j)//calculate decimal value of binary
			{	
				dec += val*bin[j];//if bit for locaiton = 1, add its value t0 dec
				val/=2;//divide value by 2 for next iteration
			}
			tryvol = dec*ss;//calculate tryvol with step size and dec value of binary
			cout<<setfill(' ')<<setw(10)<<setprecision(7)<<tryvol<<"    "<< setw(binwidth-bits);//display results
			for(int j = 0; j<bits;++j)//display binary value
				cout<<bin[j];
			cout<<"    "<<setw(4)<<i+1<<endl;//display step
			if (tryvol == vol)//if voltages are equal, quit loop
				quit = 1;
			if (tryvol < vol&&i!=bits)//if tryvol is less tan vol, increase next bit in binary
				bin[i+1] = 1;
			if (tryvol > vol)//if tryvol is too great, set current bit to 0, and next to 1
			{
				bin[i] = 0;
				if(i!=bits)// set next to 1 so long as not already operating on lsb
				bin[i+1] = 1;
			}
		
		}

		cout <<"\nThe analog voltage calculated is: "<< tryvol <<endl;//display final voltage
		error = 100 - (tryvol*100)/vol;//calculate error persent
		cout<< "The percent error is: " << error<<"%"<<endl;//display error percent
		cout<<"Would you like to repeat this program? Type 'y' for yes or 'n' for no:";////askto repeat
		repeat = choose();//get valid character
	}while (repeat == 'y');//repeat while input is yes
	return 0;
}


char choose()//function to return y or n valid characters
{
	string input;//string for input
	char real;//input tested, if iput is 1 character
	unsigned long int strsize;//size of input
	getline (cin, input);//get input, with spaces
	strsize = input.size();//get input size
	for(;;)//infinite loop, exits with returns of valid values
	{
		if(strsize==3||strsize==2)//if input could be yes or no
		{
			if(input == "Yes"||input=="yes"||input=="YES")//if input is yes, return a y
			{
			return 'y';
			}
			else if (input == "No"||input == "no"||input=="NO")// if input is a no, return n
			{
			return 'n';
			}
			else cout <<"Invalid input. Try again: ";//anything else is invalid
			getline (cin, input);//get new input
			strsize = input.size();//get new size
		}
		else if (strsize==1)//if input is y or n
		{
			real = input[0];//get first character as a character
			if (real == 'y'||real == 'Y')//if y, return y
			{
				return 'y';
			}
			if (real == 'n'||real == 'N')//if n, return n
			{
				return 'n';
			}
			else cout <<"Invalid input. Try again: ";//anything else is invalid
			getline (cin, input);
			strsize = input.size();
		}
		else if (strsize>3||strsize<1)//if nput is too long or no input
		{
		cout <<"Invalid input. Try again: ";
		getline (cin, input);
		strsize = input.size();
		}
	}
}
double nums(bool doubl)//returns a valid double with decimal points, if doubl =
{
	string input = "         ";//input, set blank
	int dec = 0;//decimal count
	unsigned long int strsize = 0;//size of input
	char value = ' ';//value of inupt to test
	string result = "         ";//resulting valid input, as a string
	double valuefinal = 0;//final value, as a double, to return
	getline (cin, input);//get input, with spaces
	strsize = input.size();//get input size
	while (strsize>9)//largest value fro int is 2 billion
	{
		cout<<"Number too long. Enter a smaller one:";//get new value
		input = "         ";
		getline(cin, input);
		strsize = input.size();
	}
		while (strsize<1)//no input
	{
		cout<<"No input. Reenter number:";
		input = "         ";
		getline(cin, input);
		strsize = input.size();
	}
	result = "         ";//clear result string
	for(int i = 0; i<strsize;)//for length of string
	{	
		char value = ' ';//reset value
		value = input[i];//take one value from the input string
		switch(value)//switch case for that one character
		{
			case '0'://test for integer values 1 - 9, if found, set same location of result and increment i
				result[i] = '0';
				i+=1;
				break;	
			case '1':
				result[i] = '1';
				i+=1;
				break;
			case '2':
				result[i] = '2';
				i+=1;
				break;
			case '3':
				result[i] = '3';
				i+=1;
				break;
			case '4':
				result[i] = '4';
				i+=1;
				break;
			case '5':
				result[i] = '5';
				i+=1;
				break;
			case '6':
				result[i] = '6';
				i+=1;
				break;
			case '7':
				result[i] = '7';
				i+=1;
				break;
			case '8':
				result[i] = '8';
				i+=1;
				break;
			case '9':
				result[i] = '9';
				i+=1;
				break;
			case '.'://find decimal point for doubles
					if(doubl == 1 &&dec<1)//if doubles are wanted and there is less than 1 decimal point found so far
					{
						result[i] = '.';//set the value in result, increment i and decimal count
						i+=1;
						++dec;
					}
					else if(doubl == 0||dec>=1)//f decimal is not wanted or one decima counted so far
					{
						i = 0;//retart count
						dec = 0;//reset decimal count
						cout<<"Invalid number. Enter new value:";//get new value
						result = "         ";//reset strings
						input = "         ";
						getline (cin, input);//get input and length
						strsize = input.size();
						while (strsize>9)//once again test for length
						{
							cout<<"Number too long. Enter a smaller one:";
							result = "         ";
							input = "         ";
							getline(cin, input);
							strsize = input.size();
						}
						while (strsize<1)//no input
						{
							cout<<"No input. Reenter number:";
							input = "         ";
							getline(cin, input);
							strsize = input.size();
						}
					}
				break;
			default://if anything else is found, reset everyting and get new values
				i = 0;
				dec = 0;
				cout<<"Invalid number. Enter new value:";
				result = "         ";
				input = "         ";
				getline (cin, input);
				strsize = input.size();
				while (strsize>9)
				{
					cout<<"Number too long. Enter a smaller one:";
					result = "         ";
					input = "         ";
					getline(cin, input);
					strsize = input.size();
				}
				while (strsize<1)//no input
				{	
					cout<<"No input. Reenter number:";
					input = "         ";
					getline(cin, input);
					strsize = input.size();
				}
			break;
		}
	}
	valuefinal = 0;//reset final value
	valuefinal = atof(result.c_str());//urn result string to double valuefinal
	return valuefinal;	//return valuefinal to main function
}

