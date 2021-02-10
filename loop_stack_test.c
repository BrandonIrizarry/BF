#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loop_stack.h"

int main () {
  
  const char *data = "this is the symphony that Schubert never finished.\n";
  char *signpost = strchr(data, 'y');
  
  loop_stack_t *ls = NULL;
  loop_stack_push(&ls, signpost);

  signpost = strchr(data, 'S');
  loop_stack_push(&ls, signpost);

  signpost = strchr(signpost, 't');
  loop_stack_push(&ls, signpost);
  
  loop_stack_print(ls);

  assert(loop_stack_pop(&ls));
  loop_stack_print(ls);
  assert(loop_stack_pop(&ls));

  loop_stack_print(ls);
  loop_stack_pop(&ls);
  loop_stack_pop(&ls);
  loop_stack_pop(&ls);
  loop_stack_pop(&ls);
  
  loop_stack_print(ls);
  
  loop_stack_free(ls);

  printf("%p %d\n", (void*)ls, ls == NULL);
  return EXIT_SUCCESS;
}
  

