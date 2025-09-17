#include <stdio.h>

#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap* V, int index);
void insertFirst(int *L, VHeap *V, int elem);
void insertLast(int *L, VHeap *V, int elem);
void delete(int *L, VHeap *V, int elem);
void display(int L, VHeap V);

int main()
{
    return 0;
}

void initialize(VHeap *V)
{
    V->avail = 0;
}

int allocSpace(VHeap *V)
{
    if(V->avail != -1)
    {
        
    }
}

void deallocSpace(VHeap *V, int index)
{
    V->H[index].next = V->avail;
    V->avail = index;
}

void delete(int *L, VHeap *V, int elem)
{
    int *trav, temp;
    trav = L;
    while(*trav != -1 && V->H[*trav].elem != elem)
    {
        trav = &V->H[*trav].next;
    }

    if(*trav != -1)
    {
        temp = *trav;
        *trav = V->H[*trav].next;
        deallocSpace(V, temp);
    }
}