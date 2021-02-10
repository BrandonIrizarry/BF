typedef struct loop_stack {
    char* startp;
    struct loop_stack *next;
} loop_stack_t;


void loop_stack_free (loop_stack_t *const topref);
void loop_stack_print (loop_stack_t *top);
char *loop_stack_pop (loop_stack_t **topref);
char* loop_stack_peek (loop_stack_t *top);
void loop_stack_push (loop_stack_t **topref, char* prog);

