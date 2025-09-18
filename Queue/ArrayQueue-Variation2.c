#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 6

typedef struct
{
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue *initialize();
bool isFull(Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int front(Queue *q);
void sort(Queue *q);
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
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 2);
    enqueue(q, 7);
    display(q);
    sort(q);
    display(q);
    return 0;
}

Queue *initialize()
{
    Queue *q = malloc(sizeof(Queue));
    q->front = 1;
    q->rear = 0;
    return q;
}

bool isFull(Queue *q)
{
    return q->front == (q->rear + 2) % MAX;
}

bool isEmpty(Queue *q)
{
    return q->front == (q->rear + 1) % MAX;
}

void enqueue(Queue *q, int value)
{
    if (isFull(q))
    {
        return;
    }

    q->rear = ((q->rear + 1) % MAX);
    q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    int value = q->items[q->front];
    q->front = ((q->front + 1) % MAX);

    return value;
}

int front(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    return q->items[q->front];
}

void sort(Queue *q)
{
    int n = (q->rear - q->front + MAX + 1) % MAX;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            int *arr1 = &q->items[(q->front + j) % MAX];
            int *arr2 = &q->items[(q->front + j + 1) % MAX];
            if(*arr1 > *arr2)
            {
                int t = *arr1;
                *arr1 = *arr2;
                *arr2 = t;
            }
        }
    }
}

void display(Queue *q)
{
    printf("Queue: ");
    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->front;
    while (1)
    {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}