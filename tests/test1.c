#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define DEBUG 1

/*
#define LINEBUFFER_SIZE 1024
#define LINEBORDER_SIZE lines
#define COLUMNBORDER_SIZE maxLineLength
*/

#define TFILEMAP_SIZE tfilestat.st_size

#define ERRPRINTF(...) fprintf(stderr,__VA_ARGS__)

#if(DEBUG)
#define DBGPRINTF(...) printf(__VA_ARGS__);
#endif

//FILE vars
char* tfilemap;
int tfilefd = -1;
struct stat tfilestat;

unsigned int i, j, lines = 0, tmpLineChars = 0, maxLineChars = 0, minLineChars = -1;

//List to mark borders in rows and columns
unsigned char * rowBorder, columnBorder;

//TABLE vars & defs
char * table;
#define TABLE_WIDTH maxLineChars
#define TABLE_HEIGHT lines

//Catch SIGINT and close & free everything
void interrupt_handler(int sig)
{
	close(tfilefd);
	
	exit(0);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		ERRPRINTF("Usage: test1 FILENAME\n");
		return 1;
	}

	if(signal(SIGINT, interrupt_handler) == SIG_ERR)
	{
		ERRPRINTF("Error: Unable to set interrupt handler!\n");
		return 5;
	}
	
	//Open file
	if((tfilefd = open(argv[1],O_RDWR | O_CREAT)) < 0)
	{
		ERRPRINTF("Error: Unable to open file!\n");
		return 2;
	}
	
	//Get file stats
	if(fstat(tfilefd,&tfilestat) == -1)
	{
		ERRPRINTF("Error: Unable access file stats!\n");
		return 3;
	}
	
	DBGPRINTF("Filesize of tfile is %d bytes\n",TFILEMAP_SIZE);
	
	//Map file into virtual memory
	if((tfilemap = (char *) mmap(NULL, TFILEMAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, tfilefd, 0)) == NULL)
	{
		ERRPRINTF("Error: Unable to map file!\n");
		return 4;
	}
	
	//Find out information about file height and width
	for(i = 0; i < TFILEMAP_SIZE; i++)
	{
		if(tfilemap[i] == '\n')
		{
			lines++;
			if(tmpLineChars > maxLineChars)
			{
				maxLineChars = tmpLineChars;
			}
			if(tmpLineChars < minLineChars)
			{
				minLineChars = tmpLineChars;
			}
			tmpLineChars = 0;
		}
		else
		{
			tmpLineChars++;
		}
	}
	DBGPRINTF("File is %d lines long, the longest line cosists of %d chars, the shortest of %d chars.\n", lines, maxLineChars, minLineChars);
	
	
	
	
/*
	if((tablefile = fopen(argv[1], "r+")) == NULL)
	{
		printf("Error: Unable to read file!");
		return 2;
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

	unsigned char lineBorder[LINEBORDER_SIZE];
	unsigned char columnBorder[COLUMNBORDER_SIZE];

	memset(lineBorder,0,LINEBORDER_SIZE);
	memset(columnBorder,0,COLUMNBORDER_SIZE);	

	return 0;
*/
}
