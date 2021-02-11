#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

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
	continue;
      } else {
	push(++ip);
	continue;
      }
    } else if (ch == ']') {
      if (data_buffer[dp] == 0) {
	pop();
	ip++;
	continue;
      } else {
	ip = peek();
	continue;
      }
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
