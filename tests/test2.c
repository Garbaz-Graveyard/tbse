#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "errorconsts.h"

#define DEBUG 1


#define ERRPRINTF(...) fprintf(stderr,__VA_ARGS__)

#if(DEBUG)
#define DBGPRINTF(...) printf(__VA_ARGS__);
#else
#define DBGPRINTF(...) 0
#endif

#define VALIDCOLUMNBORDER(ch) (ch == '|' || ch == '+') //Add unicode support ?
#define VALIDLINEBORDER(ch)   (ch == '-' || ch == '+' || ch == '\n' || ch == '\r' || ch == '\0') //Add unicode support ?

#define LINEBORDER_SIZE (lines)
#define COLUMNBORDER_SIZE (maxLineLength)

FILE* tablefile;

#define TABLEBUFFER_SIZE (maxLineLength * lines)
char * tablebuffer;

#define LINEBUFFER_SIZE 4096
char lineBuffer[LINEBUFFER_SIZE], tmpChar;


unsigned int tmpLineLength = 0, /*minLineLength = 0 ,*/ maxLineLength = 0 , lines = 0, currLine = 0;

void quit(const int exitCode)
{	
	if(tablefile != NULL) fclose(tablefile);
	if(tablebuffer != NULL) free(tablebuffer);
	exit(exitCode);
}

//Catch SIGINT and close & free everything
void interrupt_handler(int sig)
{
	quit(0);
}

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("Usage: test2 FILENAME\n");
		quit(ERROR_ARGS);
	}
	
	if(signal(SIGINT, interrupt_handler) == SIG_ERR)
	{
		ERRPRINTF("Error: Unable to set interrupt handler!\n");
		quit(ERROR_INTHANDLE);
	}

	if((tablefile = fopen(argv[1], "r+")) == NULL)

	{
		printf("Error: Unable to read file!");
		quit(ERROR_OPENFILE);
	}
	
	while(fgets(lineBuffer,LINEBUFFER_SIZE,tablefile) != NULL)
	{
		tmpLineLength = strlen(lineBuffer);
		if(tmpLineLength > maxLineLength)
		{
			maxLineLength = tmpLineLength;
		}
		lines++;
	}
	printf("File has %d lines and the longest line is %d characters long\n", lines, maxLineLength);
	
	tablebuffer = (char *) malloc(TABLEBUFFER_SIZE);
	fseek(tablefile,0,SEEK_SET);
	while(fgets(lineBuffer,LINEBUFFER_SIZE,tablefile) != NULL && currLine <= lines)
	{
		memcpy(&tablebuffer[currLine * maxLineLength],lineBuffer,maxLineLength);

		currLine++;
	}

#if(DEBUG)
	for(unsigned int i = 0; i < TABLEBUFFER_SIZE; i++)
	{
		putchar(tablebuffer[i]);
	}
#endif

	unsigned char lineBorder[LINEBORDER_SIZE];
	unsigned char columnBorder[COLUMNBORDER_SIZE];

	memset(lineBorder,0,LINEBORDER_SIZE);
	memset(columnBorder,0,COLUMNBORDER_SIZE);	
	
	for(unsigned int i = 0; i < maxLineLength; i++)
	{
		if(VALIDCOLUMNBORDER(tablebuffer[i]))
		{
			columnBorder[i] = 1;
			for(unsigned int j = 0; j < lines; j++)
			{
				if(!VALIDCOLUMNBORDER(tablebuffer[j * maxLineLength + i]))
				{
					columnBorder[i] = 0;
				}
			}
		}
	}

	for(unsigned int i = 0; i < lines; i++)
	{
		if(VALIDLINEBORDER(tablebuffer[lines * i]))
		{
			lineBorder[i] = 1;
			for(unsigned int j = 0; j < maxLineLength; j++)
			{
				if(!(VALIDLINEBORDER(tablebuffer[i * maxLineLength + j])))
				{
					lineBorder[i] = 0;
				}
			}
		}
	}

	for(unsigned int i = 0; i < COLUMNBORDER_SIZE; i++)
	{
		if(columnBorder[i]) printf("Column %u is a border\n", i);
	}
	for(unsigned int i = 0; i < LINEBORDER_SIZE; i++)
	{
		if(lineBorder[i]) printf("Line %u is a border\n", i);
	}

	quit(0);
}
