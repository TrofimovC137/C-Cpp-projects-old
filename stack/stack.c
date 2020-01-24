typedef struct my_stack{
    int value;
    struct my_stack* next_element;
}my_stack;
void push(my_stack** stack,int value){
    my_stack* buf=malloc(sizeof(my_stack));
    buf->value=value;
    buf->next_element=*stack;
    *stack=buf;
}
int pop(my_stack** stack){
    int value;
    my_stack* free_element;
    free_element=*stack;
    *stack=(*stack)->next_element;
    value=free_element->value;
    free(free_element);
    return value;
}
