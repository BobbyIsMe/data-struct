#include <stdio.h>
#include <stdlib.h>
#define LENGTH 4

typedef struct
{
    int *elemPtr;
    int count;
    int max;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List, int data);
void display(List L);

int main()
{
    List L;
    L = initialize(L);
    L = insertPos(L, 1, 0);
    display(L);
    L = insertPos(L, 2, 1);
    display(L);
    L = insertPos(L, 5, 2);
    display(L);
    L = insertSorted(L, 6);
    display(L);
    L = deletePos(L, 0);
    display(L);
    L = deletePos(L, 1);
    display(L);
    return 0;
}

List initialize(List L)
{
    L.elemPtr = malloc(sizeof(int) * LENGTH);
    L.max = LENGTH;
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position)
{
    if (position > L.count || position < 0)
    {
        return L;
    }

    if (L.count == L.max)
    {
        L.max *= 2;
        L.elemPtr = realloc(L.elemPtr, sizeof(int) * L.max);
    }

    for (int i = L.count; i > position; i--)
    {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }
    L.elemPtr[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position)
{
    if (position > L.count || position < 0)
    {
        return L;
    }

    L.elemPtr[position] = 0;
    L.count--;
    for (int i = position; i < L.count; i++)
    {
        L.elemPtr[i] = L.elemPtr[i + 1];
    }
    return L;
}

int locate(List L, int data)
{
    for (int i = 0; i < L.count; i++)
    {
        if (L.elemPtr[i] == data)
            return i;
    }
    return -1;
}

List insertSorted(List L, int data)
{
    int i;
    for (; i < L.count && L.elemPtr[i] < data; i++)
    {

    }
    return insertPos(L, data, i);
}

void display(List L)
{
    printf("elem: [");
    if (L.count != 0)
        printf("%d", L.elemPtr[0]);
    for (int i = 1; i < L.count; i++)
    {
        printf(", %d", L.elemPtr[i]);
    }
    printf("]\ncount: %d\nmax: %d\n\n", L.count, L.max);
}
