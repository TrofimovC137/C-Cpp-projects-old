#include "stack.h"
int main()
{
    int i;
    my_stack stack;
    stack.value=0;
    stack.next_element=NULL;
    for(i=0;i<10;i++){
        printf("stack push %d\n",i);
        push(&stack,i);
    }
    printf("\n");
    for(i=0;i<10;i++){
        printf("stack pop %d\n",pop(&stack));
    }
    return 0;
}
