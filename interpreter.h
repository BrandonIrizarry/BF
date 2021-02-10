// Maximum size of memory used by BF program
#define MAX_MEM 10L

// Maximum size of a BF program
#define MAX_PROG 30000L

// The interpreter ensures that the input
// program has balanced square-brackets:
// the maximum possible number of loops
// in a syntactically valid BF program can
// never be more than half the program's total
// size.
#define MAX_LOOP (MAX_PROG / 2)

char *loop_stack[MAX_LOOP];
long sp = 0;

void push (char *prog);
bool
