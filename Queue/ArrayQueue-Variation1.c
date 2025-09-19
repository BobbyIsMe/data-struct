#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

typedef struct
{
    int items[MAX];
    int count;
} List;

typedef struct
{
    List list;
    int front;
    int rear;
} Queue;

Queue *initialize();
bool isFull(Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int front(Queue *q);
void enqueueSorted(Queue *s, int value);
void sort(Queue *q);
void display(Queue *q);

int main()
{
    Queue *q = initialize();
    enqueueSorted(q, 5);
    enqueueSorted(q, 2);
    enqueueSorted(q, 3);
    enqueueSorted(q, 6);
    display(q);
    // enqueue(q, 5);
    // enqueue(q, 4);
    // enqueue(q, 3);
    // display(q);
    // printf("Dequeued: %d\n", dequeue(q));
    // display(q);
    // printf("Dequeued: %d\n", dequeue(q));
    // printf("Dequeued: %d\n", dequeue(q));
    // display(q);
    // enqueue(q, 3);
    // enqueue(q, 4);
    // enqueue(q, 5);
    // enqueue(q, 1);
    // enqueue(q, 7);
    // display(q);
    // sort(q);
    // display(q);
    return 0;
}

void enqueueSorted(Queue *s, int value)
{
    Queue *temp = initialize();

    while (!isEmpty(s) && front(s) <= value)
    {
        enqueue(temp, dequeue(s));
    }

    enqueue(temp, value);

    while (!isEmpty(s))
    {
        enqueue(temp, dequeue(s));
    }

    while (!isEmpty(temp))
    {
        enqueue(s, dequeue(temp));
    }
}

Queue *initialize()
{
    Queue *q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    q->list.count = 0;
    return q;
}

bool isFull(Queue *q)
{
    return q->list.count == MAX;
}

bool isEmpty(Queue *q)
{
    return q->list.count == 0;
}

void enqueue(Queue *q, int value)
{
    if (isFull(q))
    {
        return;
    }

    if (isEmpty(q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = ((q->rear + 1) % MAX);
    }
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    int value = front(q);
    q->front = ((q->front + 1) % MAX);

    q->list.count--;
    if (isEmpty(q))
    {
        q->front = -1;
        q->rear = -1;
    }

    return value;
}

int front(Queue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    return q->list.items[q->front];
}

void sort(Queue *q)
{
    for (int i = 0; i < q->list.count - 1; i++)
    {
        for (int j = 0; j < q->list.count - i - 1; j++)
        {
            int *arr1 = &q->list.items[(q->front + j) % MAX];
            int *arr2 = &q->list.items[(q->front + j + 1) % MAX];
            if (*arr1 > *arr2)
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
    Queue copy = *q;
    while (!isEmpty(q))
    {
        printf("%d ", dequeue(q));
    }
    *q = copy;
    printf("\n");
}