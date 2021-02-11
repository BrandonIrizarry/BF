#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

// Use three sentinel values of -1 to prevent
// pointers (one at the beginning, one in the middle,
// one at the end) from running past their valid
// ranges.
// The left-half of memory is reserved for BF's
// data block. The right half is used to buffer
// loop-code.
#define MEMBLOCK 30000L
#define START_LOOPSEGMENT (1 + MEMBLOCK + 1)
#define TOTALMEM (2*MEMBLOCK + 3)

char memory[TOTALMEM];

void right (char **ptr);
void left (char **ptr);
/* void loop_mode (FILE **input, char *const base, char *mem); */
void execute (char ch, char **mem);
void print_all ();

int main (int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *input = fopen(argv[1], "r");

  memory[0] = -1;
  memory[START_LOOPSEGMENT - 1] = -1;
  memory[TOTALMEM - 1] = -1;

  // initialize all memory
  for (long i = 0; i < TOTALMEM; i++)
    if (memory[i] != -1) memory[i] = 0;
       
  char *mem = memory + 1;
  char *const base = memory + START_LOOPSEGMENT;
    
  int ch;

  // The interpreter's main loop.
  while (1) {
    if ((ch = fgetc(input)) == EOF) break;
    
    if (ch == '[') {
      char *loop = base;

      while ((ch = fgetc(input)) != EOF && ch != ']')
	*loop++ = ch;

      if (ch == EOF) {
	fprintf(stderr, "Unbalanced loop\n");
	exit(EXIT_FAILURE);
      }

      while (*mem != 0)
	for (char *l = base; l != loop; l++)
	  execute(*l, &mem);
    } else if (!isspace(ch))
      execute(ch, &mem);
  }

  print_all();
  
  fclose(input);
  return EXIT_SUCCESS;
}

// Move a pointer across the memory field with bounds-checking.
void right (char **ptr) {
  ++*ptr;

  if (**ptr < 0) {
    fprintf(stderr, "Program causes '%p' to trespass into invalid memory\n", (void*)*ptr);
    exit(EXIT_FAILURE);
  }
}

void left (char **ptr) {
  --*ptr;

  if (**ptr < 0) {
    fprintf(stderr, "Program causes '%p' to trespass into invalid memory\n", (void*)*ptr);
    exit(EXIT_FAILURE);
  }
}

void print_all () {
  printf("Data Segment:\n");
  
  for (long i = 1; i < START_LOOPSEGMENT - 1; i++)
    if (memory[i] > 0)
      printf("[%ld]=%d\n", i - 1, memory[i]);

  printf("Loop segment:\n");

  for (long i = START_LOOPSEGMENT; i < TOTALMEM; i++)
    if (memory[i] > 0)
      printf("[%ld]=%d\n", i - 1, memory[i]);
}
    

void execute (char ch, char **mem) {
  switch (ch) {
  case '+':
    ++**mem; break;
  case '-':
    --**mem; break;
  case '<':
    left(mem); break;
  case '>':
    right(mem); break;
  case '.':
    putchar(**mem); break;
  case ',':
    **mem = getchar(); break;
  default:
    break;
  } 
}
