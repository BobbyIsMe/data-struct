#include <stdio.h>

#define MAX 4

typedef struct
{
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct
{
    HeapSpace H;
    int avail;
} VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, int index);
void insertFirst(int *L, VHeap *V, int elem);
void insertLast(int *L, VHeap *V, int elem);
void delete(int *L, VHeap *V, int elem);
void display(int L, VHeap V);

int main() {
    VHeap V;
    int L = -1;   // start with an empty list

    // Initialize virtual heap
    initialize(&V);

    // Insert elements
    insertFirst(&L, &V, 10);  // List: 10
    display(L, V);
    insertLast(&L, &V, 20);   // List: 10 20
    insertLast(&L, &V, 30);   // List: 10 20 30
    insertFirst(&L, &V, 5);   // List: 5 10 20 30
    display(L, V);

    // Delete an element
    printf("Deleting 20...\n");
    delete(&L, &V, 20);       // List: 5 10 30
    display(L, V);

    // Insert more elements (to test reuse of freed space)
    insertLast(&L, &V, 40);   // List: 5 10 30 40
    display(L, V);

    // Attempt to insert beyond capacity
    printf("Attempting to insert 50...\n");
    insertLast(&L, &V, 50);   // Should fail since MAX=4
    display(L, V);

    return 0;
}

void initialize(VHeap *V)
{
    for (int i = 0; i < MAX - 1; i++)
    {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
    V->avail = 0;
}

int allocSpace(VHeap *V)
{
    int p = V->avail;
    if (p != -1)
    {
        V->avail = V->H[p].next;
    }
    return p;
}

void deallocSpace(VHeap *V, int index)
{
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int *L, VHeap *V, int elem)
{
    int newNode = allocSpace(V);
    if (newNode == -1)
    {
        printf("Insertion failed: no space available.\n");
        return;
    }

    V->H[newNode].elem = elem;
    V->H[newNode].next = *L;

    *L = newNode;
}


void insertLast(int* L, VHeap* V, int elem) {
    int newNode = allocSpace(V);
    if (newNode == -1) {
        printf("No space available in virtual heap.\n");
        return;
    }

    V->H[newNode].elem = elem;

    V->H[newNode].next = -1;

    int *trav = L;
    while (*trav != -1) {
        trav = &V->H[*trav].next;
    }

    *trav = newNode;
}


void delete(int *L, VHeap *V, int elem)
{
    int *trav, temp;
    trav = L;
    while (*trav != -1 && V->H[*trav].elem != elem)
    {
        trav = &V->H[*trav].next;
    }

    if (*trav != -1)
    {
        temp = *trav;
        *trav = V->H[*trav].next;
        deallocSpace(V, temp);
    }
}

void display(int L, VHeap V) {
    if (L == -1) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    for (int curr = L; curr != -1; curr = V.H[curr].next) {
        printf("%d (next: %d) ", V.H[curr].elem, V.H[curr].next);
    }
    printf("\n");
}