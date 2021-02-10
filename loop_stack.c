/* 
this program segfaults when printing a loop_stack.
fix.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loop_stack.h"

void loop_stack_push (loop_stack_t **topref, char* prog) {
  if (*topref == NULL) {
    *topref = malloc(sizeof(loop_stack_t));
    (*topref)->startp = prog;
    (*topref)->next = NULL;

    return;
  }

  loop_stack_t *ls = malloc(sizeof(loop_stack_t));
  loop_stack_t *hold = *topref;
  *topref = ls;

  (*topref)->next = hold;
  (*topref)->startp = prog;
}

char* loop_stack_peek (loop_stack_t *top) {
  return top->startp;
}

char *loop_stack_pop (loop_stack_t **topref) {
  if (*topref == NULL) {
    return NULL;
  }

  char *prog = (*topref)->startp;
  
  loop_stack_t* anchor = *topref;
  *topref = anchor->next;
  free(anchor);

  return prog;
}

void loop_stack_print (loop_stack_t *top) {
  while (top != NULL) {
    printf("%p %c ", top->startp ,*top->startp);
    top = top->next;
  }

  printf("\n");
}

void loop_stack_free (loop_stack_t *const topref) {
  if (topref == NULL) return;
  
  loop_stack_t *hold;
  loop_stack_t *iter = topref;
  
  while (iter != NULL) {
    hold = iter;
    iter = iter->next;
    free(hold);
  }
}

