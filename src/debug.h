
#ifdef DEBUG
#if(DEBUG)
#define DBGPRINTF(...) fprintf(stderr,__VA_ARGS__);
#else
#define DBGPRINTF(...) 0
#endif
#endif
