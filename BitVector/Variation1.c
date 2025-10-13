#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 8

void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void delete(unsigned char *set, int element);
bool find(unsigned char set, int element);
unsigned char Union(unsigned char A, unsigned char B);
unsigned char intersection(unsigned char A, unsigned char B);
unsigned char difference(unsigned char A, unsigned char B);
void display(unsigned char set);

int main()
{
    unsigned char setA = 0, setB = 0;

    // Initialize sets
    initialize(&setA);
    initialize(&setB);

    // Insert elements
    insert(&setA, 1);
    insert(&setA, 3);
    insert(&setB, 2);
    insert(&setB, 3);

    // Display sets
    display(setA); // Should show: 1, 3
    display(setB); // Should show: 2, 3

    // Find an element
    printf("Find 3 in A: %s\n", find(setA, 3) ? "Found" : "Not Found");
    printf("Find 4 in A: %s\n", find(setA, 4) ? "Found" : "Not Found");


    // Delete an element
    delete (&setA, 1);
    display(setA); // Should show: 3

    // Union of sets
    unsigned char unionResult = Union(setA, setB);
    display(unionResult); // Should show: 2, 3

    // Intersection of sets
    unsigned char intersectionResult = intersection(setA, setB);
    display(intersectionResult); // Should show: 3

    // Difference of sets
    unsigned char differenceResult = difference(setA, setB);
    display(differenceResult); // Should show: (empty)

    return 0;
}

void initialize(unsigned char *set)
{
    *set = 0;
}

void insert(unsigned char *set, int element)
{
    if (element < 0 || element >= MAX_SIZE)
    {
        return;
    }

    unsigned char bitmask = 1 << element;
    *set |= bitmask;
}

void delete(unsigned char *set, int element)
{
    if (element < 0 || element >= MAX_SIZE)
    {
        return;
    }

    unsigned char bitmask = 1 << element;
    bitmask = ~bitmask;

    *set &= bitmask;
}

bool find(unsigned char set, int element)
{
    unsigned char bitmask = 1 << element;
    return (set & bitmask) != 0;
}

unsigned char Union(unsigned char A, unsigned char B)
{
    return A | B;
}

unsigned char intersection(unsigned char A, unsigned char B)
{
    return A & B;
}

unsigned char difference(unsigned char A, unsigned char B)
{
    return A & ~B;
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
