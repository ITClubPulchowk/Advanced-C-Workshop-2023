#include <stdio.h>

#define STACK_SIZE 50

typedef struct stack{
    int arr[STACK_SIZE];
    int top;
}Stack;


void initStack(Stack *s){
    s->top = -1;
}

void push(Stack *s, int value){
    // check for overflow
    if (s->top + 1 < STACK_SIZE){
        // increase stack top
        s->top++;
        // add new value at top
        s->arr[s->top] = value;
        printf("Pushed %d\n", value);
    }
    else {
        printf("Stack overflow: Cant push %d\n", value);
    }
}

int pop(Stack *s){
    // check for underflow
    if (s->top > -1){
        // get value at top of stack
        int value = s->arr[s->top];

        // decrease stack top
        s->top--;
        printf("Popped %d\n", value);

        return value;
    }
    else{
        printf("Stack underflow: Empty");
        return(-1);
    }
}

// displays the content of stack
void stackDump(Stack *s){
    printf("| ");
    for (int i=0; i<=s->top; i++){
        printf("%d | ", s->arr[i]);
    }
    printf("\n");
}


int main(){
    Stack s;
    initStack(&s);

    push(&s, 1);
    stackDump(&s);
    push(&s, 2);
    stackDump(&s);
    push(&s, 3);
    stackDump(&s);
    pop(&s);
    stackDump(&s);
    push(&s, 4);
    stackDump(&s);
    pop(&s);
    stackDump(&s);

    return 0;
}
