#include <stdio.h>

//Switch to altenate screen:
#define TERM_ALT()  printf("\e7\e[?47h")
//Switch back:
#define TERM_BACK() printf("\e[2J\e[?47l\e8")
//Go to position:
#define TERM_POS(x,y) printf("\e[%d;%dH",y,x)

