#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_KEY_LENGTH 20

typedef struct node {
    char key[MAX_KEY_LENGTH];
    int val;
    struct node* next;
} Node;

int hash(const char* key) 
{
    int hash = 0;
    while(*key) 
    {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

void insert(Node* D[], const char* key, int val) 
{
    int index = hash(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->val = val;
    newNode->next = D[index];

    D[index] = newNode;
    printf("Inserted %s (%d)\n", key, val);
}

Node* search(Node* D[], const char* key) 
{
    int index = hash(key);
    Node* trav = D[index];

    while(trav != NULL) 
    {
        if(strcmp(trav->key, key) == 0)
            return trav;
        trav = trav->next;
    }
    return NULL;
}

void deleteKey(Node* D[], const char* key) 
{
    int index = hash(key);

    Node** curr = &D[index];

    while(*curr != NULL && strcmp((*curr)->key, key) != 0) 
    {
        curr = &((*curr)->next);
    }

    if(*curr != NULL) 
    {
        Node* del = *curr;
        *curr = (*curr)->next;
        free(del);
        printf("Deleted %s\n", key);
    } else {
        printf("Could not delete key %s, not found\n", key);
    }
}

void display(Node* D[]) 
{
    printf("Displaying VALORANT Teams with their number of wins:\n");
    for(int i = 0; i < TABLE_SIZE; i++) 
    {
        printf("Index %d: ", i);
        Node* temp = D[i];

        while(temp != NULL) 
        {
            printf("%s (%d) -> ", temp->key, temp->val);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() 
{
    Node* D[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        D[i] = NULL;
    }

    insert(D, "NRG", 1);
    insert(D, "Sentinels", 2);
    insert(D, "LOUD", 1);
    insert(D, "Fnatic", 3);
    insert(D, "PRX", 1);

    display(D);

    Node* team = search(D, "NRG");
    if (team != NULL)
        printf("Found %s (%d)\n", team->key, team->val);
    else
        printf("NRG not found\n");

    deleteKey(D, "Sentinels");

    display(D);

    return 0;
}