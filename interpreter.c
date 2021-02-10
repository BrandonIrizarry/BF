#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_program (const char *fname);

void mem_right (char **m);
void mem_left (char **m);

int main (int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *const program  = read_program(argv[1]);

  // Give memory two extra cells, for sentinels on either side
  // that flag whether the pointer has reached invalid memory.
  char *const memory = calloc(MAX_MEM + 2, sizeof(*memory));

  // Establish left and right bounds to the BF machine's memory.
  memory[0] = -1;
  memory[MAX_MEM + 1] = -1; 

  // Start the data pointer, mem, at the first valid memory cell
  char *mem = memory + 1;
  
  int ch;
  char *prog = program;

  while ((ch = *prog)) {
    if (ch == '[') {
      if (*mem == 0) {
	
      } else {
	push(mem);
	prog++;
      }
    } else {
      switch (ch) {
      case '>':
	mem_right(&mem);
	break;
      case '<':
	mem_left(&mem);
	break;
      case '+': // addition loops back to 0
	*mem = (*mem + 1) % 128;
	break;
      case '-': // subtraction loops back to 127
	--*mem;
	if (*mem < 0) {
	  assert(*mem == -1);
	  *mem = 127;
	}
	break;	
      default:
	break;
      }

      // in the absence of a looping construct,
      // merely advance the program counter by 1.
      prog++;
    }
  }


  // for now, simply dump the final state of memory.
  for (char *p = memory + 1; *p >= 0; ++p) {
    const char *fmt = (p == mem) ? ">%d " : "%d "; 
    printf(fmt, *p);
  }
  
  printf("\n");
  
  free(memory);
  free(program);
  return EXIT_SUCCESS;
}

// The buffer containing the program's source.
// Because of loops ('[', ']'), we need to make sure that
// an extra '[' doesn't careen the program off its edge.
// An extra ']' is easily detectable as an error, by means
// of a stack; and an extra '[' would simply cause us
// to hit the null-byte at the end of our program buffer.
// The easiest way, perhaps, is to simply check if '[' and ']'
// are balanced at "read time", when we're actually
// gulping the program in for the first time.
char *read_program (const char *fname) {
   char *program = calloc(MAX_IP + 1, sizeof(*program));
  
  int ch;

  // read in the source
  FILE *stream = fopen(fname, "r");
  long i;

  long brackets = 0;
  
  for (i = 0; (ch = fgetc(stream)) != EOF && i < MAX_IP; i++) {
    if (ch == '[') brackets++;
    if (ch == ']') brackets--;
    
    program[i] = ch;
  }

  fclose(stream);

  if (ch != EOF) {
    fprintf(stderr, "file not finished being read (maximum source size is %ld bytes)\n", i);
    exit(EXIT_FAILURE);
  }

  if (brackets != 0) {
    fprintf(stderr, "Mismatched loop brackets in program, will not execute.\n");
    exit(EXIT_FAILURE);
  }
  
  return program;
}

// increment mem, but guard against falling off the edge of memory.
void mem_right (char **memref) {
  ++*memref;

  if (**memref < 0) {
    fprintf(stderr, "Program causes memory pointer to move too far to the right\n");
    exit(EXIT_FAILURE);
  }
}

void mem_left (char **memref) {
  --*memref;

  if (**memref < 0) {
    fprintf(stderr, "Program causes memory pointer to move too far to the left\n");
    exit(EXIT_FAILURE);
  }
}

void prog_right (char **progref) {
  *progref = (*progref == '\0') ? *progref : *progref + 1;
}
    
