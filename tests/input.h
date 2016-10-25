#include <stdio.h>
#include <termios.h>

static struct termios canTermios;
static int raw = 0;

/*
int input_setraw()

Parameters: none
Returns: 0 if successful, a number < 0 otherwise

*/
int input_setraw()
{
	if(!raw)
	{
		struct termios buffer;

		if(tcgetattr(0, &canTermios) < 0)
		{
			return -2;
		}

		buffer = canTermios;

		cfmakeraw(&buffer);

		if(tcsetattr(0,TCSAFLUSH,&buffer) < 0)
		{
			return -3;
		}
		
		raw = 1;

		return 0;
	}
	else
	{
		return -1;
	}
}

/*
int input_setcan()

Parameters: fd = Filedescriptor
Returns: 0 if successful, a number < 0 otherwise.

*/
int input_setcan()
{
	if(raw)
	{
		if(tcsetattr(0,TCSAFLUSH,&canTermios) < 0)
		{
			return -2;
		}

		raw = 0;
	}
	else
	{
		return -1;
	}
}
