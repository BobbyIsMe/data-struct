#include <stdio.h>
#include <string.h>
#define MAX 20
#define Empty " "
#define Delete -1

typedef struct {
    char code[3];
    int next;
} node;

typedef struct {
    node H[MAX];
    int avail;
} VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void insertSorted(VHeap *V, char *code);
void insert(VHeap *V, char *code);
void display(VHeap V);
void deallocSpace(VHeap *V, int index);
void delete(VHeap *V, char *code);
int hash(char *code);

int main() {
    VHeap V;
    int L = -1;   // start with an empty list

    // Initialize virtual heap
    initialize(&V);

    // Insert elements
    insertSorted(&V, "JFK");
    insertSorted(&V, "LAX");
    insertSorted(&V, "SFO");
    insertSorted(&V, "CDG");
    insertSorted(&V, "NRT");
    insertSorted(&V, "ATL");
    insertSorted(&V, "DXB");
    insertSorted(&V, "PEK");
    insertSorted(&V, "MIA");
    insertSorted(&V, "LHR");
    insertSorted(&V, "SYD");
    insertSorted(&V, "ORD");
    display(V);
    delete(&V, "ATL");
    display(V);
    insertSorted(&V, "ATL");
    display(V);
    delete(&V, "SYD");
    display(V);
    insertSorted(&V, "SYD");
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
    for (; i < (MAX) / 2; i++)
    {
        strcpy(V->H[i].code, Empty);
        V->H[i].next = -1;
    }
    V->avail = i;
    for (; i < (MAX - 1); i++)
    {
        strcpy(V->H[i].code, Empty);
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
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

void insertSorted(VHeap *V, char *code)
{
    int index = hash(code);
    if(strcmp(V->H[index].code, Empty) == 0)
    {
        V->H[index].next = -1;
        strcpy(V->H[index].code, code);
    } else {
        int newNode = allocSpace(V);
        if(newNode == -1)
        {
            return;
        }
        if(strcmp(V->H[index].code, code) > 0) //First index
        {
            strcpy(V->H[newNode].code, V->H[index].code);
            V->H[newNode].next = V->H[index].next;
            strcpy(V->H[index].code, code);
            V->H[index].next = newNode;
        } else { //Second and above index
            int *trav = &V->H[index].next; //Get next of first index
            while(*trav != -1 && strcmp(V->H[*trav].code, code) < 0) //Traverse to the node before the next node
            {
                trav = &V->H[*trav].next;
            }
            
            strcpy(V->H[newNode].code, code);
            V->H[newNode].next = *trav;
            *trav = newNode;
        }
    }
}

void insert(VHeap *V, char *code)
{
    int index = hash(code);
    int temp = index;   
    printf("%s: %d\n", code, index);
    if(strcmp(V->H[temp].code, Empty) == 0)
    {
        V->H[temp].next = -1;
        strcpy(V->H[temp].code, code);
    }
    else {
        int newNode = allocSpace(V);
    if (newNode == -1)
    {
        printf("Insertion failed: no space available.\n");
        return;
    }
    
    strcpy(V->H[newNode].code, code);
    V->H[newNode].next = -1;

        int *trav = &index;
    while (*trav != -1) {
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
    if(index == -1)
    {
        return;
    }
    
    int next = V->H[index].next;
    if(strcmp(V->H[index].code, code) == 0)
    {
        if(next != -1)
        {
        strcpy(V->H[index].code, V->H[next].code);
        V->H[index].next = V->H[next].next;
        deallocSpace(V, next);
        } else {
            strcpy(V->H[index].code, Empty);
        }
    } else {
        int *trav = &V->H[index].next;
        while(*trav != -1 && strcmp(V->H[*trav].code, code) != 0)
        {
            trav = &V->H[*trav].next;
        }
        
        int temp;
        if(*trav != -1)
        {
            temp = *trav;
            *trav = V->H[*trav].next;
            deallocSpace(V, temp);
        }
    }
}

void display(VHeap V) {
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
        printf("%d", V.avail);
    printf("\n");
}