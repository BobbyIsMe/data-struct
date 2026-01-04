#include <stdio.h>
#include <stdbool.h>
#define ARRAY_SIZE 8

typedef bool Set[ARRAY_SIZE];

void initialize(Set set);
void insert(Set set, int element);
void delete(Set set, int element);
bool find(Set set, int element);
void Union(Set A, Set B, Set C);
void intersection(Set A, Set B, Set C);
void difference(Set A, Set B, Set C);
void display(Set set);

int main()
{
     Set setA, setB;

    // Initialize sets
    initialize(setA);
    initialize(setB);

    // Insert elements
    insert(setA, 1);
    insert(setA, 3);
    insert(setB, 2);
    insert(setB, 3);

    // Display sets
    display(setA); // Should show: 1, 3
    display(setB); // Should show: 2, 3

    // Find an element
    printf("Find 3 in A: %s\n", find(setA, 3) ? "Found" : "Not Found");
    printf("Find 4 in A: %s\n", find(setA, 4) ? "Found" : "Not Found");

    // Delete an element
    delete(setA, 1);
    display(setA); // Should show: 3

    // Union of sets
    Set C;
    initialize(C);
    Union(setA, setB, C);
    display(C); // Should show: 2, 3

    // Intersection of sets
    intersection(setA, setB, C);
    display(C); // Should show: 3

    // Difference of sets
    difference(setA, setB, C);
    display(C); // Should show: (empty)
    return 0;
}

void initialize(Set set)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        set[i] = false;
    }
}

void insert(Set set, int element)
{
    if (element < 0 || element >= ARRAY_SIZE)
    {
        return;
    }

    set[element] = true;
}

void delete(Set set, int element)
{
    if (element < 0 || element >= ARRAY_SIZE)
    {
        return;
    }

    set[element] = false;
}

bool find(Set set, int element)
{
    if (element < 0 || element >= ARRAY_SIZE)
    {
        return false;
    }

    return set[element];
}

void Union(Set A, Set B, Set C)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        C[i] = A[i] || B[i] ? 1 : 0; 
        if (A[i] || B[i])
            C[i] = true;
    }
}

void intersection(Set A, Set B, Set C)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (A[i] && B[i])
            C[i] = true;
    }
}

void difference(Set A, Set B, Set C)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (A[i] && !B[i])
            C[i] = true;
    }
}

void display(Set set)
{
    printf("{");
    bool first = true;
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        if(set[i])
        if(first)
        {
            printf("%d", i);
            first = false;
        } else {
            printf(", %d", i);
        }
    }
    printf("}\n");
}
