typedef struct {
    char size;
    int content[64];
} int_stack;

int pop_stack(int_stack *stack){
    return stack->content[--stack->size];
}
int push_stack(int_stack *stack, int value){
    stack->content[stack->size++] = value;
}
char is_empty_stack(const int_stack *stack){
    return stack->size==0;
}
int peek_stack(const int_stack *stack){
    return stack->content[stack->size-1];
}