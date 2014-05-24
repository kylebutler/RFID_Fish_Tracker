/*
	Program: RFID Fish Tracker For a Raspberry Pi
	Programmer: Kyle Butler
	Date Created:11/?/13
	Date Modified:5/23/14
	Program Description: Program is designed to record any fish tags that are
	received by the system and store them in a text file. The program will 
	store the users physical location, recording start time, any fish's tag
	data and time of passing through the inductive loop, and the recording 
	finish time.
	
	~*~Note~*~
	For this code to function properly, it must include the rs232.h file,
	as well it must be compiled with the rs232.c file. These files were located
	at http://teuniz.net/RS-232/ (the two files can be extracted from the 
	RS-232.tar.gz file available on that webpage).
	To get the kbhit function to work effectively on Linux the same procedure 
	as above with the rs232 must be followed using the kbhit.h and kbhit.c files
	which I located at http://linux-sxs.org/programming/kbhit.html If using 
	this code on Windows simply uncomment the #include<conio.h> at the beginning
	of this code and kbhit should work just fine.
	Make sure to change Comport in the define accordingly for your situation
	and the receive chars define as well if you wish to change the buffer size
	
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "rs232.h"
#include "kbhit.h"
#include<unistd.h>
//#include<conio.h>
#include<time.h>
#define SIZE 256
#define COMPORT         6//16
#define BAUDRATE      9600
#define RECEIVE_CHARS   30//8 
#define SEND_CHARS      4


int main (void)
{
	char location[256];// holds location string
	int n;
    time_t curtime;
	struct tm *loctime;
	FILE *output; //file pointer
	char file1[256]; //array to hold 256 chars
	unsigned char receive_buffer[RECEIVE_CHARS];
	
	//Gathering location and file name
	printf("Input Antenna Location: ");
	gets(location);// stores users recording location
	printf("\nLocation: %s\n", location);// prints location back to user
	printf("\nEnter file name to be written: ");
	scanf("%s",file1);//scan user file path
	output=fopen(file1,"w");//open output file
		if(output==NULL) // if file path is invalid
			{
				printf("\nError - unable to open output file %s",file1);
			}
		else
			{	
				fprintf(output,"Location: %s\n", location);// prints location back to user
				
				//start time
				curtime = time (NULL);// get current time
				loctime = localtime (&curtime);// convert to local time
				fprintf(output,"\nRecording Start Time: ");
				printf("\nRecording Start Time: ");
				fprintf(output,asctime(loctime),stdout);
	 			fputs (asctime(loctime), stdout);// prints start time
	 			
	 			//pre polling 
	 			fprintf(output,"\nOpening Com Port\n");
	 			printf("\nOpening Com Port\n");
	 			if(RS232_OpenComport(COMPORT, BAUDRATE))// opens com port for TX/RX
				 {
					return(0);// if no comport, stop the program
				 }
	 			fprintf(output,"\nScanning for fish...\n");
	 			printf("\nScanning for fish...\n");
	 			
	 			//polling for data
				while(!kbhit())// poll until any key is hit
				{ 
					n=RS232_PollComport(COMPORT, receive_buffer, RECEIVE_CHARS);// waits for data to be sent over com port
					if(n>0)// if data was sent, print it, and the time, out
					{
						if(n>6)// gets rid of random data received by our controller, this if can be left out if no unwanted data is received
						{// tag processing
							receive_buffer[n] = 0;   /* always put a "null" at the end of a string! */
							printf("%s", receive_buffer );// print any value received while polling to the console
							fprintf(output, "%s", receive_buffer);// print any value received while polling to txt file
						//time stamp processing	
							curtime = time (NULL);// get current time    
    						loctime = localtime (&curtime);// convert to local time
							fprintf(output,asctime(loctime),stdout);//time stamp for the tag read
							//fprintf(output,"\n");
		 					fputs (asctime(loctime), stdout);
							//printf("\n");
						}
					}
					usleep(100000);// delays the scan 
				}
				RS232_CloseComport(COMPORT);// close com port if any key is pressed
				fflush(stdin);// flush input stream after a key is hit
				fprintf(output,"\nScanning exited, saving info\n");
				printf("\nScanning exited, saving info\n");	
		
			}	
	curtime = time (NULL);// get current time    
    loctime = localtime (&curtime);// convert to local time
    fprintf(output,"\nRecording Finish Time: ");
    printf("\nRecording Finish Time: ");
    fprintf(output,asctime(loctime),stdout);
    fputs (asctime (loctime), stdout);// prints finish time
	fclose(output);// close output file	
	system("pause");// pauses console before shutting down
	return (0);
	}
