/*
Muhammad Sulaiman Sultan: 231453415
Muhammad Sameed Gilani: 231488347
Compiler Cnstruction Section A
Assignment 1
Submitted to: M. Rauf Butt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define     msg1 "Hello"
#define msg2     "bye Bye"
#define msssg3 "sheeeesh"

void stripOffComments(char fileArg[100]);
void removeComments(char fileArg[100]);
void stripBlank();
void macroExpansion();
void getMacroHeadBody();
void includeHeaderFiles();


char fileName[100]; // Will keep the file name, from argv[1]

int main(int argc, char *argv[])
{
    printf("%s THIS IS MESSAGE", msg1);
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
        printf(msssg3);
	}
    strcpy(fileName,argv[1]);

    stripOffComments(fileName); 
    macroExpansion(); 
    includeHeaderFiles();

    msg2;


	return 0;
}