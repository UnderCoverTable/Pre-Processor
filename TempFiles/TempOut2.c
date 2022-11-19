#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void stripOffComments(char fileArg[100]);
void removeComments(char fileArg[100]);
void stripBlank();
void macroExpansion();
void getMacroHeadBody();
void includeHeaderFiles();
char fileName[100]; 
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