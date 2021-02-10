#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push (char *prog) {
  assert(sp < MAX_LOOP);
  loop_stack[sp++] = prog;
}

char* peek () {
  assert(sp > 0);
  return loop_stack[sp - 1];
}

void pop () {
  assert(sp > 0);
  loop_stack[--sp];
}
