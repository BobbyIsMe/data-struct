#include <stdio.h>
#include <stdbool.h>

int MAX_SIZE = 8 * sizeof(int);

typedef struct
{
    unsigned int field : 8;
} Set;

void initialize(Set *set);
void insert(Set *set, int element);
void delete(Set *set, int element);
bool find(Set set, int element);
Set Union(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(unsigned char set);

int main()
{
    Set setA, setB;

    // Initialize sets
    initialize(&setA);
    initialize(&setB);

    // Insert elements
    insert(&setA, 1);
    insert(&setA, 3);
    insert(&setB, 2);
    insert(&setB, 3);

    // Display sets
    display(setA.field); // Should show: 1, 3
    display(setB.field); // Should show: 2, 3

    // Find an element
    printf("Find 3 in A: %s\n", find(setA, 3) ? "Found" : "Not Found");
    printf("Find 4 in A: %s\n", find(setA, 4) ? "Found" : "Not Found");

    // Delete an element
    delete(&setA, 1);
    display(setA.field); // Should show: 3

    // Union of sets
    setA = Union(setA, setB);
    display(setA.field); // Should show: 2, 3

    // Intersection of sets
    setA = intersection(setA, setB);
    display(setA.field); // Should show: 3

    // Difference of sets
    setA = difference(setA, setB);
    display(setA.field); // Should show: (empty)
    return 0;
}

void initialize(Set *set)
{
    set->field = 0;
}

void insert(Set *set, int element)
{
    if (element < 0 || element >= MAX_SIZE)
    {
        return;
    }

    unsigned int bitmask = 1 << element;
    set->field |= bitmask;
}

void delete(Set *set, int element)
{
    if (element < 0 || element >= MAX_SIZE)
    {
        return;
    }

    unsigned int bitmask = 1 << element;
    bitmask = ~bitmask;

    set->field &= bitmask;
}

bool find(Set set, int element)
{
    unsigned int bitmask = 1 << element;
    return (set.field & bitmask) != 0;
}

Set Union(Set A, Set B)
{
    A.field = A.field | B.field;
    return A;
}

Set intersection(Set A, Set B)
{
    A.field = A.field & B.field;
    return A;
}

Set difference(Set A, Set B)
{
    A.field = A.field & ~B.field;
    return A;
}

void display(unsigned char set)
{
    printf("{");
    bool first = true;
    for (int i = 1; i < MAX_SIZE; i++)
    {
        if ((set >> i) & 1)
            if (first)
            {
                printf("%d", i);
                first = false;
            }
            else
            {
                printf(", %d", i);
            }
    }
    printf("}\n");
}
