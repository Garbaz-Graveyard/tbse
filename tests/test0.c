#include <stdio.h>
#include <unistd.h>

//Switch to altenate screen:
#define SWITCH_SCREEN printf("\033[?47h")
//Switch back:
#define SWITCH_BACK   printf("\033[?47l")

static struct termios oldTermios;

int main()
{
	SWITCH_SCREEN;
	printf("Hello World\n");
	sleep(1);
	SWITCH_BACK;
	return 0;
}
