#include <assert.h>
#include <ctype.h> 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Code used to manage a stack that records loop-starts.
#define MAX_PROGSIZE 30000
#define MAX_DATASIZE 30000
#define MAX_NUMLOOPS 15000

int loop_stack[MAX_NUMLOOPS];
int sp = 0;
bool init_complete = false;

void init ();
void push (int idx);
int peek ();
void pop ();

char program_buffer[MAX_PROGSIZE + 1];
char data_buffer[MAX_DATASIZE];

int main (int argc, char **argv) {
  assert(argc == 2);
  FILE *input = fopen(argv[1], "r");

  // Enter the program into our interpreter's program buffer.
  program_buffer[MAX_PROGSIZE] = '\0';
  
  int brackets = 0;
  int ch;
  int ip = 0;
  for (ip = 0; ip < MAX_PROGSIZE; ip++) {
    if ((ch = fgetc(input)) == EOF) break;

    switch (ch) {
    case '[':
      brackets++;
      break;
    case ']':
      brackets--;
      break;
    default:
      break;
    }
    program_buffer[ip] = ch;
  }

  assert(ch == EOF);
  assert(brackets == 0);

  // Begin manipulating the the data buffer.
  init();
  
  int dp;
  for (dp = 0; dp < MAX_DATASIZE; dp++)
    data_buffer[dp] = 0;

  dp = 0;
  ip = 0;

  do {
    ch = program_buffer[ip];

    if (ch == '[') {
      if (data_buffer[dp] == 0) {
	int brackets = -1;

	do {
	  ip++;
	  
	  if (program_buffer[ip] == '[') brackets--;
	  if (program_buffer[ip] == ']') brackets++;
	} while (brackets != 0);
	ip++;
      } else push(++ip);
    } else if (ch == ']') {
      if (data_buffer[dp] == 0) {
	pop();
	ip++;
      } else ip = peek();
    } else {
      switch (ch) {
      case '+':
	data_buffer[dp]++;
	break;
      case '-':
	data_buffer[dp]--;
	break;
      case '<':
	dp--;
	assert(dp >= 0);
	break;
      case '>':
	dp++;
	assert(dp < MAX_DATASIZE);
	break;
      case '.':
	putchar(data_buffer[dp]);
	break;
      case ',':
	data_buffer[dp] = getchar();
	break;
      default:
	break;
      }

      ip++;
    }
  } while (program_buffer[ip] != '\0');
  
  
  return EXIT_SUCCESS;
}

// The stack-related methods.
void init () {
  for (int i = 0; i < MAX_NUMLOOPS; i++)
    loop_stack[i] = 0;

  init_complete = true;
}

void push (int idx) {
  assert(init_complete && "Call 'init' first\n");
  assert(sp < MAX_NUMLOOPS);
  loop_stack[sp++] = idx;
}

int peek () {
  assert(init_complete && "Call 'init' first\n");
  assert(sp > 0);
  return loop_stack[sp - 1];
}

void pop () {
  assert(init_complete && "Call 'init' first\n");
  assert(sp > 0);
  --sp;
}
