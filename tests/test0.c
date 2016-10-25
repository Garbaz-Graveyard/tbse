#include <stdio.h>
#include <unistd.h>
#include "input.h"

//Switch to altenate screen:
#define TERM_ALT()  printf("\e7\e[?47h")
//Switch back:
#define TERM_BACK() printf("\e[2J\e[?47l\e8")

#define TERM_POS(x,y) printf("\e[%d;%dH",y,x)

int main()
{
	TERM_ALT();
	TERM_POS(0,0);
	for(int i = 1;i < 10; i++)
	{
		TERM_POS(i,i*i);
		printf("+");
	}
	printf("\n");
	
	input_setraw();
	while(getchar() != 'q');
	input_setcan();
	
	TERM_BACK();
	return 0;
}
