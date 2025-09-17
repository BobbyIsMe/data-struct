#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
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
    *L = (EPtr) malloc(sizeof(Etype));
    (*L)->count = 0;
}

void insertPos(EPtr L, int data, int position)
{
    if (position > L->count || position < 0 || L->count == MAX)
    {
        return;
    }

    for (int i = L->count; i > position; i--)
    {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[position] = data;
    L->count++;
}

void deletePos(EPtr L, int position)
{
    if (position > L->count || position < 0)
    {
        return;
    }

    L->elem[position] = 0;
    L->count--;
    for (int i = position; i < L->count; i++)
    {
        L->elem[i] = L->elem[i + 1];
    }
}

int locate(EPtr L, int data)
{
    for (int i = 0; i < L->count; i++)
    {
        if (L->elem[i] == data)
            return i;
    }
    return -1;
}

int retrieve(EPtr L, int position)
{
    if (position > L->count || position < 0)
    {
        return -99999;
    }

    return L->elem[position];
}

void insertSorted(EPtr L, int data)
{
    int i;
    for (i = 0; i < L->count; i++)
    {
        if (L->elem[i] > data)
            return insertPos(L, data, i);
    }
    return insertPos(L, data, i);
}

void display(EPtr L)
{
    printf("elem: [");
    if (L->count != 0)
        printf("%d", L->elem[0]);
    for (int i = 1; i < L->count; i++)
    {
        printf(", %d", L->elem[i]);
    }
    printf("]\ncount: %d\n\n", L->count);
}

void makeNULL(EPtr L)
{
    free(L);
}