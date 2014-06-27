/* 
Created by Girish Kumar

Program to calculate how long the fence must be, given 
the number of corners and the postion of each of them

:PROCEDURAL CODE:
*/

#include <iostream> 
#include <conio.h>
#include <iomanip>
#include <cmath>	//including the cmath header for sq.root calculations, etc.
#include <fstream>  //reading file
#include <stdio.h> // deliting file
#include <stdlib.h> //clear Screen
using namespace std;

void cal();
void leng(double &dis, double x1, double x2, double y1, double y2);
void read();
void del();

int main()
{
	int q = 0;
	while (q==0)
	{
		system("CLS");
		char choice;
		cout<<"\n\nWelcome to the MAIN MENU of the program, please choose your option: ";
		cout<<"\n\n A for Start program";
		cout<<"\n B for View Log of the co-ordinates";
		cout<<"\n C to Delete Log file";
		cout<<"\n Q for Quit program";
		cout<<"\n\n YOUR CHOICE: ";
		cin>>choice;
		switch (choice)
		{
			case 'A' :
			case 'a' : cal();
					   break;
			case 'B' :
			case 'b' : read();
					   break;
			case 'C' :
			case 'c' : del();
					   break;
			case 'Q' :
			case 'q' : q=1;
					   break;
			default  : cout <<"\n\nERROR!: your option is not a valid number. Press ANY KEY to try again" << endl;
					   getch(); //freeze the screen
					   break;
		}
	}
	cout<<"\n****END OF THE PROGRAM****\n\n";
	system("pause"); // freeze the screen
	return 0;
	
}
void del()
{
	if( remove( "log.txt" ) != 0 )
    cout<< "Error deleting file" ;
	else
    cout<< "File successfully deleted";
	cout <<"\n\n Press ANY KEY  for MAIN MENU" << endl;
	getch(); //freeze the screen
}

void read()
{
	system("CLS");
	ifstream fin;
    fin.open("log.txt");
    char ch;
	if (!fin)
		cout<<"file dosent exist";
	else 
	{
		while(!fin.eof())
		{
			fin.get(ch);
			cout << ch;
		}
	}
	fin.close();
	cout <<"\n\n Press ANY KEY  for MAIN MENU" << endl;
	getch();
}

void cal()
{
	system("CLS");
	int i, small;
	signed int c;
	ofstream fout; // creating a object for the out file
	fout.open("log.txt", ios::app); //writing all the data to the log file (append)
	double x[100], y[100], dis[100], tlen = 0; // assuming the maximum coners limit = 100
	cout<<"\nPlease enter the number of corners for the fence: ";  // Inputing the number of corners
	cin>>c;
	while (c < 2)
	{	
		cout<<"\n\nERROR! : The Entered value is less than two. Please try again\nNew Value: ";
		cin>>c;
	}
	cout<<endl;					//Next line
	for (i = 0; i < c; i++)			// loop to input the x, y co-ordinates of the given corners
	{
		cout<<"\nPlease enter the X co-ordinate of the corner no. " << i+1 <<" : ";  // X axis
		cin>>x[i];
		cout<<"Please enter the Y co-ordinate of the corner no. " << i+1 <<" : ";  // Y axis
		cin>>y[i];
	}
	cout<<"\nYour co-ordinates are entered as follows: \n";
	fout<<"\n\n\n\nYour co-ordinates are entered as follows: \n"; // writing to text file
	for (i = 0; i < c; i++) // loop used to generate the array for the X and Y co-ordinates
	{
		cout<<"X"<< i+1 <<" Y" << i+1 <<" = "<<"(" <<x[i] <<","<<y[i]<<")"<<endl; //printing the co-ordinates
		fout<<"X"<< i+1 <<" Y" << i+1 <<" = "<<"(" <<x[i] <<","<<y[i]<<")"<<endl; //Write to Text file
	}
	cout<<endl;

	//TO CALCULATE THE DISTANCE BETWEEN ALL POINTS
	for (i = 1; i <= c; i++) // loop used to calculate and print the distance
	{
		if(i==c) // if we are finding the distance between last point and first point
			leng(dis[i-1], x[0], x[i-1], y[0], y[i-1]);// To find distance between last corner and 1st corner
		else 
			leng(dis[i-1], x[i-1], x[i], y[i-1], y[i]);// To find the distance of two co
	}

	//TO DISPLAY THE DISTANCE BETWEEN ALL POINTS
	for (i = 1; i <= c; i++) // loop used to calculate and print the distance
	{
		if(i==c) // if we are finding the distance between last point and first point
			cout<<"The distance between corner " << i <<" (" <<x[i-1] <<","<<y[i-1]<<")"<<" and corner 1 (" <<x[0] <<","<<y[0]<<") is: " <<dis[i-1]<<endl;
		else 
			cout<<"The distance between corner " << i <<" (" <<x[i-1] <<","<<y[i-1]<<")"<<" and corner "<< i+1 <<" (" <<x[i] <<","<<y[i]<<") is: " <<dis[i-1]<<endl; //printing the co-ordinates
	}

	// TO FIND THE SMALLEST DISTANCE BETWEEN POINTS AND CALCULATE THE SUM OF THE LENGTH
	small = 0; // assuming that array of 0 is small at the begining
	for (i=0; i<c; i++)
	{

		tlen += dis[i]; // calculated the sum of the length
		if (dis[small]>=dis[i]) //comparing the small array with the looped array
			small = i;		
	}
	if (small+2>c)  // if the small+2 value is beyound the corner then its shifted to 0 
		cout<<"\nThe distance between corner "<< small+1 <<" and corner 1 is the smallest"; // for the last case 
	else
		cout<<"\nThe distance between corner "<< small+1 <<" and corner "<<small+2<<" is the smallest";
	cout<<"\n\nTotal length of the fence is: "<<tlen;
	fout.close();
	cout <<"\n\n Press ANY KEY for MAIN MENU" << endl;
	getch(); //freeze the screen
	cout<<endl<<endl;		 // next line 
}

void leng(double &dis, double x1, double x2, double y1, double y2) //Call by Reference is be used in order to change the actual values
{
	dis=sqrt((pow ((x2 - x1),2))+(pow ((y2 - y1),2))); //Formula to calculate the diatance of two points
}