#include <stdio.h>
#include <string.h>
#define MAX 20
#define Empty " "
#define Delete -1

typedef struct
{
    char code[3];
    int next;
} node;

typedef struct
{
    node H[MAX];
    int avail;
} VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void insertSorted(VHeap *V, char *code);
void insertUniqueSorted(VHeap *V, char *code);
void insert(VHeap *V, char *code);
void display(VHeap V);
void deallocSpace(VHeap *V, int index);
void delete(VHeap *V, char *code);
int hash(char *code);

int main()
{
    VHeap V;
    int L = -1; // start with an empty list

    // Initialize virtual heap
    initialize(&V);

    // Insert elements
    insertUniqueSorted(&V, "JFK");
    insertUniqueSorted(&V, "LAX");
    insertUniqueSorted(&V, "SFO");
    insertUniqueSorted(&V, "CDG");
    insertUniqueSorted(&V, "NRT");
    insertUniqueSorted(&V, "ATL");
    insertUniqueSorted(&V, "DXB");
    insertUniqueSorted(&V, "PEK");
    insertUniqueSorted(&V, "MIA");
    insertUniqueSorted(&V, "LHR");
    insertUniqueSorted(&V, "SYD");
    insertUniqueSorted(&V, "ORD");
    display(V);
    delete(&V, "ATL");
    display(V);
    insertUniqueSorted(&V, "ATL");
    display(V);
    delete(&V, "SYD");
    display(V);
    insertUniqueSorted(&V, "SYD");
    display(V);
    insertUniqueSorted(&V, "SYD");
    display(V);
    return 0;
}

int hash(char *code)
{
    return ((code[0] - 'A') * 26 * 26 + (code[1] - 'A') * 26 + (code[2] - 'A')) % 10;
}

void initialize(VHeap *V)
{
    int i = 0;
    for(; i < (MAX) / 2; i++)
    {
        strcpy(V->H[i].code, Empty);
        V->H[i].next = -1;
    }
    V->avail = i;
    for(; i < (MAX - 1); i++)
    {
        strcpy(V->H[i].code, Empty);
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
}

int allocSpace(VHeap *V)
{
    int p = V->avail;
    if(p != -1)
    {
        V->avail = V->H[p].next;
    }
    return p;
}

void insertSorted(VHeap *V, char *code)
{
    int index = hash(code);
    if(strcmp(V->H[index].code, code) == 0)
    {
        strcpy(V->H[index].code, code);
        return;
    }

    int trav = index;
    int prev = -1;

    while(trav != -1 && strcmp(V->H[index].code, code) < 0)
    {
        prev = trav;
        trav = V->H[trav].next;
    }

    int newNode = allocSpace(V);
    if(newNode == -1)
    {
        return;
    }

    if(prev == -1)
    {
        strcpy(V->H[newNode].code, V->H[trav].code);
        V->H[newNode].next = V->H[trav].next;
        strcpy(V->H[trav].code, code);
        V->H[trav].next = newNode;
    }
    else
    {
        strcpy(V->H[newNode].code, code);
        V->H[newNode].next = trav;
        V->H[prev].next = newNode;
    }
}

void insertUniqueSorted(VHeap *V, char *code)
{
    int index = hash(code);
    node *trav = &V->H[index];
    node *prev = NULL;

    while(1)
    {
        if(strcmp(trav->code, code) == 0) //Check if code exists
        {
        printf("[INSERT] Code %s already exists!\n", code);
        return;
        }

        if(strcmp(trav->code, code) > 0 || trav->next == -1) break;
        
        prev = trav;
        trav = &V->H[trav->next];
    }

    if(strcmp(trav->code, Empty) == 0) //Check if head is empty
    {
        strcpy(trav->code, code);
        printf("[INSERT] Code %s inserted at index %d\n", code, index);
        return;
    }

    if(strcmp(trav->code, code) < 0) //Set prev as trav if all codes are still smaller than code
        prev = trav;

    int newNode = allocSpace(V);
    if(newNode == -1)
    {
        printf("[INSERT] No available space!\n");
        return;
    }
    V->H[newNode].next = -1;

    if(prev == NULL)
    {
        strcpy(V->H[newNode].code, trav->code);
        V->H[newNode].next = trav->next;

        strcpy(trav->code, code);
        trav->next = newNode;
    }
    else
    {
        strcpy(V->H[newNode].code, code);
        V->H[newNode].next = prev->next;
        prev->next = newNode;
    }

    printf("[INSERT] Collision: Code %s inserted in sorted order at index %d.\n", code, index);
}

void insert(VHeap *V, char *code)
{
    int index = hash(code);
    printf("%s: %d\n", code, index);
    if(strcmp(V->H[index].code, Empty) == 0)
    {
        V->H[index].next = -1;
        strcpy(V->H[index].code, code);
    }
    else
    {
        int newNode = allocSpace(V);
        if(newNode == -1)
        {
            printf("Insertion failed: no space available.\n");
            return;
        }

        strcpy(V->H[newNode].code, code);
        V->H[newNode].next = -1;

        int *trav = &index;
        while(*trav != -1)
        {
            trav = &V->H[*trav].next;
        }

        *trav = newNode;
    }
}

void deallocSpace(VHeap *V, int index)
{
    V->H[index].next = V->avail;
    V->avail = index;
}

void delete(VHeap *V, char *code)
{
    int index = hash(code);
    int trav = index;
    int prev = -1;
    while(trav != -1 && strcmp(V->H[trav].code, code) != 0)
    {
        prev = trav;
        trav = V->H[trav].next;
    }

    if(strcmp(V->H[trav].code, code) != 0)
    {
        printf("Element not found!\n");
        return;
    }

    if(prev == -1)
    {
        int next = V->H[trav].next;
        if(next != -1)
        {
            strcpy(V->H[trav].code, V->H[next].code);
            V->H[trav].next = V->H[next].next;
            deallocSpace(V, next);
        }
        else
        {
            strcpy(V->H[trav].code, Empty);
        }
    }
    else
    {
        V->H[prev].next = V->H[trav].next;
        deallocSpace(V, trav);
    }
}

void display(VHeap V)
{
    printf("List: \n");
    for(int i = 0; i < (MAX) / 2; i++)
    {
        printf("%d index: ", i);
        int index = i;
        while(index != -1 && strcmp(V.H[index].code, Empty) != 0)
        {
            printf("%s (next: %d) -> ", V.H[index].code, V.H[index].next);
            index = V.H[index].next;
        }
        printf("NULL\n");
    }
    printf("Available Index: %d", V.avail);
    printf("\n");
}