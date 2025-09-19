#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 10

typedef struct
{
    int items[MAX];
    int top;
} Stack;

Stack *initialize();
bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
int top(Stack *s);
void sortList(Stack *s);
void sortStack(Stack *s);
void display(Stack *s);

int main()
{
    Stack *s = initialize();
    push(s, 5);
    push(s, 4);
    push(s, 3);
    display(s);
    printf("Popped: %d\n", pop(s));
    display(s);
    push(s, 3);
    sortStack(s);
    display(s);
    return 0;
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

void push(Stack *s, int value)
{
    if (isFull(s))
    {
        return;
    }

    s->top++;
    s->items[s->top] = value;
}

void sortStack(Stack *s) {
    Stack *temp = initialize();
    while (!isEmpty(s)) {
        int curr = pop(s);
        // Move larger elements back to the original stack
        while (!isEmpty(temp) && peek(temp) < curr) {
            push(s, pop(temp));
        }
        push(temp, curr);
    }
    // Transfer sorted elements back to original stack
    while (!isEmpty(temp)) {
        push(s, pop(temp));
    }
}

int pop(Stack *s)
{
    if (isEmpty(s))
    {
        return -1;
    }

    int value = s->items[s->top];
    s->top--;
    return value;
}

int peek(Stack *s)
{
    if (isEmpty(s))
    {
        return -1;
    }

    return s->items[s->top];
}

int top(Stack *s)
{
    return s->top;
}

void sortList(Stack *s)
{
    for (int i = 0; i < s->top ; i++)
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
    Stack copy = *s;
    while (!isEmpty(s))
    {
        printf("%d ", pop(s));
    }
    *s = copy;
    printf("\n");
}