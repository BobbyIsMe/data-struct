#include <stdio.h>
#include <stdlib.h>
#define LENGTH 4

typedef struct
{
    int *elemPtr;
    int count;
    int max;
} Etype, *EPtr;

void initialize(EPtr *L);
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, int data);
int retrieve(EPtr L, int position);
void insertSorted(EPtr, int data);
void display(EPtr L);
void makeNULL(EPtr L);

int main()
{
    EPtr L;
    initialize(&L);
    insertPos(L, 1, 0);
    display(L);
    insertPos(L, 2, 1);
    display(L);
    insertPos(L, 5, 2);
    display(L);
    insertSorted(L, 6);
    display(L);
    deletePos(L, 0);
    display(L);
    deletePos(L, 1);
    display(L);
    makeNULL(L);
    return 0;
}

void initialize(EPtr *L)
{
    *L = (EPtr)malloc(sizeof(Etype));
    (*L)->elemPtr = malloc(sizeof(int) * LENGTH);
    (*L)->max = LENGTH;
    (*L)->count = 0;
}

void insertPos(EPtr L, int data, int position)
{
    if (position > L->count || position < 0)
    {
        return;
    }

    if (L->count == L->max)
    {
        L->max *= 2;
        L->elemPtr = realloc(L->elemPtr, sizeof(int) * L->max);
    }

    for (int i = L->count; i > position; i--)
    {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }
    L->elemPtr[position] = data;
    L->count++;
}

void deletePos(EPtr L, int position)
{
    if (position > L->count || position < 0)
    {
        return;
    }

    L->elemPtr[position] = 0;
    L->count--;

    for (int i = position; i < L->count; i++)
    {
        L->elemPtr[i] = L->elemPtr[i + 1];
    }
}

int locate(EPtr L, int data)
{
    for (int i = 0; i < L->count; i++)
    {
        if (L->elemPtr[i] == data)
            return i;
    }
    return -1;
}

void insertSorted(EPtr L, int data)
{
    int i = 0;
    for (; i < L->count && L->elemPtr[i] < data; i++)
    {

    }
    insertPos(L, data, i);
}

int retrieve(EPtr L, int position)
{
    if (position > L->count || position < 0)
    {
        return -99999;
    }

    return L->elemPtr[position];
}

void display(EPtr L)
{
    printf("elem: [");
    if (L->count != 0)
        printf("%d", L->elemPtr[0]);
    for (int i = 1; i < L->count; i++)
    {
        printf(", %d", L->elemPtr[i]);
    }
    printf("]\ncount: %d\nmax: %d\n\n", L->count, L->max);
}

void makeNULL(EPtr L)
{
    free(L->elemPtr);
    free(L);
}