#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 10

typedef struct
{
    char items[MAX];
    int top;
} Stack;

Stack *initialize();
bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, char value);
char pop(Stack *s);
char peek(Stack *s);
char top(Stack *s);
void sortList(Stack *s);
void codeValidator(Stack *s);
void display(Stack *s);

int main()
{
    Stack *s = initialize();
    push(s, '(');
    push(s, '(');
    push(s, '(');
    push(s, '(');
    codeValidator(s);
    return 0;
}

void codeValidator(Stack *s)
{
    Stack *close = initialize();
    while (!isEmpty(s))
    {
        char val = pop(s);
        if (val == ')' || val == '}' || val == ']')
            push(close, val);
        else if (val == '(' || val == '{' || val == '[' )
        {
            char val1 = peek(close);
            if ((val == '(' && val1 == ')') || (val == '{' && val1 == '}') || (val == '[' && val1 == ']'))
            {
                pop(close);
            } else {
                printf("Code is invalid");
                return;
            }
        }
    }

    if(!isEmpty(close))
    printf("Code is invalid");
    else
    printf("Code is valid");
}

Stack *initialize()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

bool isFull(Stack *s)
{
    return s->top == MAX - 1;
}

bool isEmpty(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, char value)
{
    if (isFull(s))
    {
        return;
    }

    s->top++;
    s->items[s->top] = value;
}

char pop(Stack *s)
{
    if (isEmpty(s))
    {
        return -1;
    }

    char value = s->items[s->top];
    s->top--;
    return value;
}

char peek(Stack *s)
{
    if (isEmpty(s))
    {
        return -1;
    }

    return s->items[s->top];
}

char top(Stack *s)
{
    return s->items[s->top];
}

void sortList(Stack *s)
{
    for (int i = 0; i < s->top; i++)
    {
        for (int j = 0; j < s->top - i; j++)
        {
            if (s->items[j] > s->items[j + 1])
            {
                int temp = s->items[j];
                s->items[j] = s->items[j + 1];
                s->items[j + 1] = temp;
            }
        }
    }
}

void display(Stack *s)
{
    printf("Stack: ");
    if (isEmpty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    for (int i = s->top; i >= 0; i--)
    {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}