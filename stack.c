#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "defs.h"

int loop_stack[MAX_NUMLOOPS];
int sp = 0;
bool ready = false;

void init () {
  for (int i = 0; i < MAX_NUMLOOPS; i++)
    loop_stack[i] = 0;

  ready = true;
}

void push (int idx) {
  assert(ready && "Call 'init' first\n");
  assert(sp < MAX_NUMLOOPS);
  loop_stack[sp++] = idx;
}

int peek () {
  assert(ready && "Call 'init' first\n");
  assert(sp > 0);
  return loop_stack[sp - 1];
}

void pop () {
  assert(ready && "Call 'init' first\n");
  assert(sp > 0);
  --sp;
}
