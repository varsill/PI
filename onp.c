#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct stack {
    int* elements;
    int top;
    int max_size;
} stack;

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


int toInt(char* entry)
{
    int result = 0;
    int m = 1;
   // printf("%d", strlen(entry));
    for(int i = strlen(entry)-1; i>=0; i--)
    {

        result+=(entry[i]-'0')*m;
        m*=10;
    }
    return result;
}

typedef enum entry_type {number, add, subtract, multiply, divide} entry_type;

entry_type parse(char* raw) {
    if (raw[0] == '+') return add;
    if (raw[0] == '-') return subtract;
    if (raw[0] == '*') return multiply;
    if (raw[0] == '/') return divide;
    return number;
}

/****************************
* implement functions below *
****************************/

void do_add(stack* s) {
    int arg1  = pop(s);
    int arg2 = pop(s);
    push(s,arg2+arg1);
}

void do_subtract(stack* s) {
    int arg1  = pop(s);
    int arg2 = pop(s);
    push(s, arg2-arg1);
}

void do_multiply(stack* s) {
    int arg1  = pop(s);
    int arg2 = pop(s);
    push(s, arg2*arg1);
}

void do_divide(stack* s) {
    int arg1  = pop(s);
    int arg2 = pop(s);
    push(s, arg2/arg1);
}

int read_and_calculate(int operands_count, int max_entry_size) {
    stack* operands = new_stack(operands_count);
    int ile = 0;
    char* entry = malloc((max_entry_size+1)*sizeof(char));
    while(ile!=operands_count ||  operands->top!=1) {
        for(int i=0; i<max_entry_size; i++) entry[i] = '\0';
        scanf("%s", entry);
        switch(parse(entry))
        {
        case number:
            {
                push(operands, toInt(entry));
                ile++;
                break;
            }
        case add:
            {
               do_add(operands);
                break;
            }
        case subtract:
            {
               do_subtract(operands);
                break;
            }

        case multiply:
            {
               do_multiply(operands);
                break;
            }
        case divide:
            {
                do_subtract(operands);
                break;
            }
        }
    }

    int result = pop(operands);
    delete_stack(operands);
    free(entry);
    return result;
}

int main() {
    int operands_count, max_entry_size;
    scanf("%d", &operands_count);
    scanf("%d", &max_entry_size);
    printf("%d\n", read_and_calculate(operands_count, max_entry_size));

}
