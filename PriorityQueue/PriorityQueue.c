#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int duration;
} Task;

typedef struct {
    Task* heap;
    int size;
    int capacity;
} MinHeap;

void heapify(MinHeap* pq, int i);
void insert(MinHeap* pq, Task task);
Task extractMin(MinHeap* pq);
void display(MinHeap* pq);
void resizeHeap(MinHeap* pq);

int main() 
{
    MinHeap pq;
    pq.size = 0;
    pq.capacity = 2;
    pq.heap = (Task*)malloc(pq.capacity * sizeof(Task));

    if(pq.heap == NULL) 
    {
        printf("Memory allocation failed!\n");
        return -1;
    }

    insert(&pq, (Task){"Relax", 5});
    insert(&pq, (Task){"Play", 10});
    insert(&pq, (Task){"Shopping", 30});
    insert(&pq, (Task){"Study", 45});
    insert(&pq, (Task){"Talk", 14});

    printf("\nPriority Queue after insertions:\n");
    display(&pq);

    printf("\nExtracting tasks by priority:\n");
    while(pq.size > 0) 
    {
        Task t = extractMin(&pq);
        printf("Extracted: %s (%d min)\n", t.name, t.duration);

        printf("\nRemaining Queue:\n");
        display(&pq);
    }

    free(pq.heap);
    return 0;
}

void heapify(MinHeap* pq, int i) 
{
    int smallest = i;
    do {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < pq->size && pq->heap[left].duration < pq->heap[smallest].duration)
            smallest = left;

        if(right < pq->size && pq->heap[right].duration < pq->heap[smallest].duration)
            smallest = right;

        if (smallest != i)
        {
            Task temp = pq->heap[i];
            pq->heap[i] = pq->heap[smallest];
            pq->heap[smallest] = temp;
        }

        i = smallest;
    } while(smallest != i);
}

void resizeHeap(MinHeap* pq) 
{
    pq->capacity *= 2;
    pq->heap = (Task*)realloc(pq->heap, pq->capacity * sizeof(Task));
    if(pq->heap == NULL) 
    {
        printf("Memory allocation failed!\n");
        exit(-1);
    }
}

void insert(MinHeap* pq, Task task) 
{
    if (pq->size >= pq->capacity) 
    {
        resizeHeap(pq);
    }

    pq->heap[pq->size] = task;
    pq->size++;

    int i = pq->size - 1;
    int parent = (i - 1) / 2;
    while(pq->heap[parent].duration > pq->heap[i].duration) 
    {
        Task temp = pq->heap[i];
        pq->heap[i] = pq->heap[parent];
        pq->heap[parent] = temp;

        i = parent;
        parent = (i - 1) / 2;
    }
}

Task extractMin(MinHeap* pq) 
{
    if(pq->size == 0) 
    {
        Task empty = {"", -1};
        return empty;
    }

    Task minTask = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    heapify(pq, 0);
    return minTask;
}

void display(MinHeap* pq) 
{
    if (pq->size == 0) 
    {
        printf("Priority Queue is empty.\n");
        return;
    }

    for (int i = 0; i < pq->size; i++) 
    {
        printf("Task: %s | Duration: %d\n", pq->heap[i].name, pq->heap[i].duration);
    }
}