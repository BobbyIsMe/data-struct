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
int isMember(VHeap V, int S, char *code);
void insertUniqueSorted(VHeap *V, int *S, char *code);
void Union(VHeap *U, int *S, VHeap V1, int S1, VHeap V2, int S2);
void Intersect(VHeap *I, int *S, VHeap V1, int S1, VHeap V2, int S2);
void Difference(VHeap *D, int *S, VHeap V1, int S1, VHeap V2, int S2);
void display(VHeap V, int S);
void deallocSpace(VHeap *V, int index);
void delete(VHeap *V, int *S, char *code);

int main()
{
    VHeap V1;
    int S1 = -1;
    initialize(&V1);
    insertUniqueSorted(&V1, &S1, "Aa");
    insertUniqueSorted(&V1, &S1, "Dd");
    insertUniqueSorted(&V1, &S1, "Cc");
    VHeap V2;
    int S2 = -1;
    initialize(&V2);
    insertUniqueSorted(&V2, &S2, "Bb");
    display(V2, S2);
    VHeap U;
    int S = -1;
    Union(&U, &S, V1, S1, V2, S2);
    display(U, S);
    insertUniqueSorted(&V2, &S2, "Cc");
    insertUniqueSorted(&V2, &S2, "Cc");
    VHeap I;
    int SI = -1;
    Intersect(&I, &SI, V1, S1, V2, S2);
    display(I, SI);
    VHeap D;
    int SD = -1;
    Difference(&D, &SD, V1, S1, V2, S2);
    display(D, SD);
    return 0;
}

void initialize(VHeap *V)
{
    for (int i = 0; i < MAX - 1; i++)
    {
        strcpy(V->H[i].code, Empty);
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

void insertUniqueSorted(VHeap *V, int *S, char *code)
{
    int *trav = S;
    while (*trav != -1)
    {
        if(strcmp(V->H[*trav].code, code) == 0)
        {
            printf("Element already exists!\n");
            return;
        }
        if(strcmp(V->H[*trav].code, code) > 0)
        break;
        trav = &V->H[*trav].next;
    }

    int newNode = allocSpace(V);
    if(newNode == -1)
    {
        return;
    }
    strcpy(V->H[newNode].code, code);
    V->H[newNode].next = *trav;
    *trav = newNode;
}

void delete(VHeap *V, int *S, char *code)
{
    int *trav = S;
    while (*trav != -1 && strcmp(V->H[*trav].code, code) != 0)
    {
        trav = &V->H[*trav].next;
    }

    if (*trav != -1)
    {
        int temp = *trav;
        *trav = V->H[*trav].next;
        deallocSpace(V, temp);
    }
    else
    {
        printf("%s is not found!\n", code);
    }
}

void display(VHeap V, int S)
{
    printf("{");
    int trav = S;
    int first = 1;
    while (trav != -1)
    {
        if (first)
        {
            printf("%s", V.H[trav].code);
            first = 0;
        }
        else
        {
            printf(", %s", V.H[trav].code);
        }
        trav = V.H[trav].next;
    }
    printf("}\n");
}

int isMember(VHeap V, int S, char *code)
{
    int trav = S;
    while (trav != -1)
    {
        if (strcmp(V.H[trav].code, code) == 0)
            return 1;
        trav = V.H[trav].next;
    }
    return 0;
}

void Union(VHeap *U, int *S, VHeap V1, int S1, VHeap V2, int S2)
{
    *U = V1;
    *S = S1;
    int trav = S2;
    while (trav != -1)
    {
        insertUniqueSorted(U, S, V2.H[trav].code);
        trav = V2.H[trav].next;
    }
}

void Intersect(VHeap *I, int *S, VHeap V1, int S1, VHeap V2, int S2)
{
    initialize(I);
    *S = -1;
    while (S1 != -1)
    {
        if (isMember(V2, S2, V1.H[S1].code))
        {
            insertUniqueSorted(I, S, V1.H[S1].code);
        }
        S1 = V1.H[S1].next;
    }
}

void Difference(VHeap *D, int *S, VHeap V1, int S1, VHeap V2, int S2)
{
    initialize(D);
    *S = -1;
    while (S1 != -1)
    {
        if (!isMember(V2, S2, V1.H[S1].code))
        {
            insertUniqueSorted(D, S, V1.H[S1].code);
        }
        S1 = V1.H[S1].next;
    }
}