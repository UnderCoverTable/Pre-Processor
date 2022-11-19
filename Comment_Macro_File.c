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

void stripOffComments(char fileArg[100]);
void removeComments(char fileArg[100]);
void stripBlank();
void macroExpansion();
void getMacroHeadBody();
void includeHeaderFiles();


char fileName[100]; // Will keep the file name, from argv[1]

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}
    strcpy(fileName,argv[1]);

    stripOffComments(fileName); 
    macroExpansion(); 
    includeHeaderFiles();


	return 0;
}

void stripOffComments(char fileArg[100]){
    /*
        All comments and blank lines from the source file are removed and written to out1.c
        The Source file is not changed
    */

	removeComments(fileArg);
    stripBlank();

}

void removeComments(char fileArg[100])
{
	FILE *SourceFile; 
    FILE *outFile;

	SourceFile = fopen(fileArg,"r");
    outFile = fopen("out1.c","w+");
	char* buff = (char*) malloc(sizeof(char)*100000);
	char* buff2 = (char*) malloc(sizeof(char)*100000);

	char c = ' ';
	int idx = 0;

	while (c != EOF)
	{
		c = fgetc(SourceFile);
		//printf("%c",c);
		buff[idx] = c;
		idx++;
	}

	int i,j = 0;
	int flag = 0;
	while(buff[i] != EOF)
	{
		if(buff[i] == '/') 
		{
			if(buff[i+1] == '/')
				while(buff[i] != '\n')
					i++;
			if (buff[i+1] =='*')
			{
				i+=2;
				while(buff[i] != EOF)
				{
					if(buff[i-1] == '*' && buff[i] == '/')
					{
						i++;
						break;
					}
					i++;
				}
			}
		}
		fputc(buff[i],outFile);
		i++;
		j++;
	}
	fclose(SourceFile);
	fclose(outFile);
}

void stripBlank(){
    /*
        Function will remove any blank lines from the file and updates the out1.c file.
    */

    // Creating file handlers
    FILE *SourceFile;
    FILE *TempFile;
    FILE *OutFile;

    // Open the source file from previous function(For Reading) and create a temp file(For Writing)
    SourceFile = fopen("out1.c","r");
    TempFile = fopen("Temp","w+");

    char* buffer = (char*) malloc(sizeof(char)*100000); // Memory allocated 

    // Reads the file character by character and writes it to the temp file
    char currC = ' ';
    currC = fgetc(SourceFile);

    while(currC != EOF){
        fputc(currC,TempFile);
        currC = fgetc(SourceFile);
    }

    fclose(SourceFile);
    fclose(TempFile);


    // Opens the temp file(For reading) and the Out1.c file(For writing)
    TempFile = fopen("Temp", "r");
    OutFile = fopen("out1.c","w+");
    
    // Reads the temp file and writes each line to the buffer
    while(fgets(buffer,100000,TempFile) != NULL){
        int i = 0;
        int check = 1; // Flag to see if there is text at any point in the line

        if(buffer[0] == '\n' ) continue;
           
        
        if(buffer[0] == ' ' || buffer[0] == '\t' ){         // Will see if the line starts with a space or tab
            while(buffer[i] == ' ' || buffer[i] == '\t' ){ //  It will then see if the line has any text in it
                i++;

                if(buffer[i] == '\n' || buffer[i] == '\0'){ // Line has no text in it so it is not written to out file
                    check = 0;
                    break;
                }
                 
            }
        
            if(check == 1) fprintf(OutFile,"%s",buffer); // The line has some text in it so it will be written to out file
            
             
        }
        else fprintf(OutFile,"%s",buffer); // If the line starts with any text it is written to the out file
    }
    fclose(TempFile);
   // remove("Temp"); // Temp file is deleted
    fclose(OutFile);
}

void macroExpansion(){
    /*
        All macros are expanded in the file
    */

    getMacroHeadBody(); // files are created with the macro heads and bodies respectively

    FILE *SourceFile;
    FILE *HeadFile;
    FILE *BodyFile;
    FILE *OutFile;

    SourceFile = fopen("TempOut2.c","r"); // Temp file from getMacroHeadBody() is opened to be read
    OutFile = fopen("out2.c","w+");  // out2.c is created to be written to
    HeadFile = fopen("TempHead","r");
    BodyFile = fopen("TempBody","r");

    char* buff = (char*) malloc(sizeof(char)*100000);
    char* buffAfterBodyStr = (char*) malloc(sizeof(char)*100000);

    char* buffHead = (char*) malloc(sizeof(char)*100000);
    char* buffHeadTemp = (char*) malloc(sizeof(char)*100000);
    
    char* buffBody = (char*) malloc(sizeof(char)*100000);
    char* buffBodyTemp = (char*) malloc(sizeof(char)*100000);


    int i = 0;
    int j = 0;
    int newLineFlag = 0;
    char *test;
    int val;
    char headLastChar = ' ';

    
    while(fgets(buff,100000,SourceFile) != NULL){ // Each line is read from the source file
        // This will allow us to check each macro head, whether its written in each single line thats being read

        while(fgets(buffHead,100000,HeadFile) != NULL){ // Each macro head from the macro head file is read
            newLineFlag++;

            fgets(buffBody,100000,BodyFile); // We read the body file and check its first character
            val = atoi(&buffBody[0]); // its first char is the number of line its written on
                                    // This allows us to pick the correct macro body, according to the macro head being considered
            while(val != newLineFlag){
                printf("%d",newLineFlag);
                fgets(buffBody,100000,BodyFile);
                val = atoi(&buffBody[0]);
            }
            
            i = 1;
            j = 0;
            while(buffBody[i] != '\n'){ // We remove the first char(line number) and skip the \n and writes
                buffBodyTemp[j] = buffBody[i];// the body to a buffer
                i++;
                j++;
            }            // buffBodyTemp == BODY of macro in question


            i = 0;
            j = 0;
            while(buffHead[i] != '\n'){ // skips \n and writes the macro head to a buffer
                buffHeadTemp[j] = buffHead[i];
                i++;
                j++;
            }
                        // buffHeadTemp == HEAD of macro in question

            headLastChar = buffHeadTemp[i-1]; // To keep track of the last char of the macro head
            

            test = strstr(buff,buffHeadTemp); // Gives us a pointer to the first char of the macro head, if it is in the,
            i = 0;                             // current line from the source file
            j = 0;

            if(test){ // Current macro is in the current line

                while(test[i] != headLastChar){ // It gets to the last character of the macro head
                    i++;
                }
                i++;
                while(test[i] != '\n'){ // now that the index (i) is at the end of the macro head, 
                    buffAfterBodyStr[j] = test[i]; // we then store the chars after macro head in a buffer
                    i++;
                    j++;
                }
                buffAfterBodyStr[j] = '\n';

                strcpy(test,buffBodyTemp); // the pointer test is at the start of the macro head
                                        // we copy the macro body onto that pointer. So all the chars from the start
                                        // of the macro head till end of line is replaced with the macro body

                strcat(test,buffAfterBodyStr); // To restore the text after the macro body that was removed,
                                            // we concat the macro body with the buffer, in which we previously stored the 
                                            // text after the macro head

            }

        // Buffers are reset to write the next iteration of items
        memset(buffHeadTemp,0,100000);
        memset(buffBodyTemp,0,100000);
        memset(buffAfterBodyStr,0,100000);


        j = 0;
        i = 0;

        }
        newLineFlag = 0;
        memset(buffBody,0,100000);

        // rewind the files to recheck every head with the new line from fgets
        rewind(HeadFile);
        rewind(BodyFile);

        fputs(buff,OutFile); // buffer with the updated line, with macro body replaced with head(if head was in the line)
                            // is written to out2.c

    }
    fclose(OutFile);
}

void getMacroHeadBody()
{
    /*
        This will write the macro Heads to a file and macro Bodys to a seperate file.
        They will be placed in order in each file, so the head and macro are mapped to the same lines.
    */
    FILE *SourceFile;
    FILE *TempOutFile;
    FILE *HeadFile;
    FILE *BodyFile;

    SourceFile = fopen("out1.c","r"); // out1.c from prev fucntion is opened to be read
    TempOutFile = fopen("TempOut2.c","w+"); // a temp file is opened to be written
    HeadFile = fopen("TempHead","w+");
    BodyFile = fopen("TempBody","w+");

    char* buff = (char*) malloc(sizeof(char)*100000);
    int i = 0;
    int bodyLineCount = 1; // Will track the line number the macro body is stored on

    while(fgets(buff,100000,SourceFile) != NULL){

        // Reads the input file line by line. line with #define will be caught
        if((buff[0] == '#' && buff[1] == 'd' && buff[2] == 'e' && buff[3] == 'f' && buff[4] == 'i' && buff[5] == 'n' && buff[6] == 'e') || (buff[0] == '#' && buff[1] == 'D' && buff[2] == 'E' && buff[3] == 'F' && buff[4] == 'I' && buff[5] == 'N' && buff[6] == 'E')) {
            
            i = 7;
            while(buff[i] == ' ' || buff[i] == '\t'){ //Skips spaces after #define
                i++;
            }
              
            while(buff[i] != ' '){ // Its at the Macro head now, itll be written to its file
                fputc(buff[i],HeadFile);
                i++;
            }
            fputc('\n',HeadFile);

            while(buff[i] == ' ' ){ // Spaces after the macro head are skipped
                i++;
            }
            fprintf(BodyFile,"%d",bodyLineCount);
            bodyLineCount++;

            while(buff[i] != '\n'){     // Its at the macro body.itll written to its file
                fputc(buff[i],BodyFile);
                i++;
            }
            fputc('\n',BodyFile);
        }
        else{
            fputs(buff,TempOutFile); // It wont write the #define to the the tempOut2 file
        }


    }
    fclose(SourceFile);
    fclose(TempOutFile);
    fclose(HeadFile);
    fclose(BodyFile);
}

void includeHeaderFiles()
{
	char* buff = (char*) malloc(sizeof(char)*100000); // Will store each line read
	char* include = (char*) malloc(sizeof(char)*100000); // Will store the include files

	FILE *fp;
	FILE *final;

	fp = fopen("out2.c","r");
	final = fopen("final.c","w+");

	while(fgets(buff,100000,fp) != NULL)
	{

		int i = 0;
		if (strstr(buff,"stdio.h") != NULL)
		{
			FILE *stdio;
			stdio = fopen("pa1_stdio", "r");
			while(fgets(include, 100000, stdio) != NULL)
				fputs(include, final);
			fclose(stdio);
		}
		else if (strstr(buff,"stdlib.h") != NULL)
		{
			FILE *stdlib;
			stdlib = fopen("pa1_stdlib", "r");
			while(fgets(include, 100000, stdlib) != NULL)
				fputs(include, final);
			fclose(stdlib);
		}
		else if (strstr(buff,"string.h") != NULL)
		{
			FILE *string;
			string = fopen("pa1_string", "r");
			while(fgets(include, 100000, string) != NULL)
				fputs(include, final);
			fclose(string);
		}
		else
		{
			fputs(buff, final);
		}
	}
	fclose(final);
    fclose(fp);

	final = fopen("final.c", "r");
	while(fgets(buff,100000,final) != NULL)
	{
		printf("%s",buff);
	}
	fclose(final);
}
