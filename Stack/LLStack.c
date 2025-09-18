#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack* initialize();
bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
int top(Stack *s);
void sortList(Stack *s);
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
    push(s, 7);
    sortList(s);
    display(s);
    return 0;
}

Stack *initialize()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s; 
}

bool isFull(Stack *s)
{
    return false;
}

bool isEmpty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s)
{
    if(isEmpty(s))
    {
        return -1;
    }

    Node *temp = s->top;
    int value = s->top->data;

    s->top = s->top->next;
    free(temp);
    return value;
}

int peek(Stack *s)
{
    if(isEmpty(s))
    {
        return -1;
    }

    return s->top->data;
}

void sortList(Stack *s)
{
    Node *temp;
    Node *end = NULL;
    int swapped = 1;
    while(swapped)
    {
        temp = s->top;
        swapped = 0;
        while(temp->next != NULL && temp->next != end)
        {
            if(temp->data > temp->next->data)
            {
                int c = temp->data;
                temp->data = temp->next->data;
                temp->next->data = c;
                if(!swapped) swapped = 1;
            }
            temp = temp->next;
        }
        end = temp;
    }
}

void display(Stack *s)
{
    printf("Stack: ");
    if(isEmpty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    Node *temp = s->top;
    while(temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}