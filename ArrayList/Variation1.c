#include <stdio.h>
#define MAX 10

typedef struct
{
    int elem[MAX];
    int count;
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
    L = insertPos(L, 6, -1);
    display(L);
    L = insertSorted(L, 6);
    display(L);
    L = deletePos(L, 0);
    display(L);
    L = deletePos(L, 1);
    display(L);
    printf("Locating: 1, result: %d\n", locate(L, 1));
    printf("Locating: 2, result: %d\n", locate(L, 2));
    return 0;
}

List initialize(List L)
{
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position)
{
    if (position > L.count || position < 0 || L.count == MAX)
    {
        return L;
    }

    for (int i = L.count; i > position; i--)
    {
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position)
{
    if (position > L.count || position < 0)
    {
        return L;
    }

    L.elem[position] = 0;
    L.count--;
    for (int i = position; i < L.count; i++)
    {
        L.elem[i] = L.elem[i + 1];
    }
    return L;
}

int locate(List L, int data)
{
    for (int i = 0; i < L.count; i++)
    {
        if (L.elem[i] == data)
            return i;
    }
    return -1;
}

List insertSorted(List L, int data)
{
    int i;
    for (i = 0; i < L.count; i++)
    {
        if (L.elem[i] > data)
            return insertPos(L, data, i);
    }
    return insertPos(L, data, i);
}

void display(List L)
{
    printf("elem: [");
    if (L.count != 0)
        printf("%d", L.elem[0]);
    for (int i = 1; i < L.count; i++)
    {
        printf(", %d", L.elem[i]);
    }
    printf("]\ncount: %d\n\n", L.count);
}
