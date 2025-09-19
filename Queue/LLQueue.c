#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

Queue *initialize();
bool isFull(Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int front(Queue *q);
void display(Queue *q);

int main()
{
    Queue *q = initialize();
    enqueue(q, 5);
    enqueue(q, 4);
    enqueue(q, 3);
    display(q);
    printf("Dequeued: %d\n", dequeue(q));
    display(q);
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q);
    enqueue(q, 3);
    display(q);
    return 0;
}

Queue *initialize()
{
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isFull(Queue *q)
{
    return false;
}

bool isEmpty(Queue *q)
{
    return q->front == NULL;
}

void enqueue(Queue *q, int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (isEmpty(q))
    {
        q->front = newNode;
    }
    else
    {
        q->rear->next = newNode;
    }
    q->rear = newNode;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    Node *temp = q->front;
    int value = temp->data;
    q->front = temp->next;

    free(temp);

    if (isEmpty(q))
    {
        q->rear = NULL;
    }

    return value;
}

int front(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    return q->front->data;
}

void display(Queue *q)
{
    printf("Queue: ");
    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }

    // Node *temp = q->front;
    // while (temp != NULL)
    // {
    //     printf("%d -> ", temp->data);
    //     temp = temp->next;
    // }

    Queue *temp = initialize();
    while(!isEmpty(q))
    {
        enqueue(temp, dequeue(q));
    }
    
    while(!isEmpty(temp))
    {
        int val = dequeue(temp);
        printf("%d -> ", val);
        enqueue(q, val);
    }

    printf("NULL\n");
}