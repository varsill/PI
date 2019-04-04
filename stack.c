#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
    int* elements;
    int top;
    int max_size;
} stack;

/*****************************
* implements functions below *
*****************************/

void push(stack* s, int n) {
s->elements[s->top]=n;
s->top++;
}

int pop(stack* s) {
int result = s->elements[s->top-1];
s->top--;
return result;
}

bool is_empty(stack* s) {
    if(s->top==0) return true;
    return false;
}

stack* new_stack(int size) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->elements = (int*)malloc(size*sizeof(int));
    s->max_size=size;
    s->top = 0;
    return s;
}

void delete_stack(stack* s) {
    free(s->elements);
    free(s);
}

int main() {
    int size;
    scanf("%d", &size);
    stack* s = new_stack(size);
    int tmp;

    for(int i=0; i<size; i++)
    {
        scanf("%d", &tmp);
        push(s, tmp);
    }

    for(int i=0; i<size; i++)
    {
        printf("%d \n", pop(s));
    }

    delete_stack(s);

}
