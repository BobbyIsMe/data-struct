#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct
{
    Node *head;
    int count;
} List;

List *initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deleteLast(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void sortList(List *list);
void display(List *list);

int main()
{
    List *list = initialize();
    insertFirst(list, 1);
    display(list);

    insertLast(list, 2);
    display(list);

    insertLast(list, 3);
    display(list);

    insertPos(list, 4, 2);
    display(list);

    insertPos(list, 5, 4);
    display(list);

    insertFirst(list, 7);
    display(list);

    deleteStart(list);
    display(list);

    deleteLast(list);
    display(list);

    deletePos(list, 1);
    display(list);

    sortList(list);
    display(list);

    printf("Retrieve result for index %d: %d\n\n", 1, retrieve(list, 1));
    printf("Retrieve result for index %d: %d\n\n", 4, retrieve(list, 4));

    printf("Locate result for data %d: %d\n\n", 3, locate(list, 3));
    printf("Locate result for data %d: %d\n\n", 6, locate(list, 6));

    empty(list);
    display(list);
    return 0;
}

List *initialize()
{
    List *list = malloc(sizeof(List));
    if (list == NULL)
    {
        printf("Error allocating memory.");
        return NULL;
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

void empty(List *list)
{
    Node *head = list->head;
    for (int i = 0; i < list->count; i++)
    {
        free(head);
        head = head->next;
    }

    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error allocating memory.");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    list->count++;

    Node *head = list->head;
    if (head == NULL)
    {
        list->head = newNode;
        return;
    }

    newNode->next = head;
    list->head = newNode;
}

void insertLast(List *list, int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error allocating memory.");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;
    list->count++;

    Node *head = list->head;
    if (head == NULL)
    {
        list->head = newNode;
        return;
    }

    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

void insertPos(List *list, int data, int index)
{
    if (index > list->count || index < 0)
    {
        return;
    }

    if (index == 0)
    {
        insertFirst(list, data);
        return;
    }

    if (index == list->count)
    {
        insertLast(list, data);
        return;
    }

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error allocating memory.");
        return;
    }

    newNode->data = data;
    list->count++;

    Node *current = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void sortList(List *list)
{
    Node *temp = NULL;
    Node *end = NULL;
    int start = 1;
    while(start)
    {
        start = 0;
        temp = list->head;
        while(temp->next != NULL && temp->next != end)
        {
            if(temp->data > temp->next->data)
            {
                int c = temp->data;
                temp->data = temp->next->data;
                temp->next->data = c;

                if(!start)
                start = 1;
            }
            temp = temp->next; 
        }
        end = temp;
    }
}

void deleteStart(List *list)
{
    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list)
{
    Node *current = list->head;
    for (int i = 0; i < list->count - 2; i++)
    {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    list->count--;
}

void deletePos(List *list, int index)
{
    if (index > list->count || index < 0)
    {
        return;
    }

    if (index == 0)
    {
        deleteStart(list);
        return;
    }

    if (index == list->count)
    {
        deleteLast(list);
        return;
    }

    Node *current = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        current = current->next;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);

    list->count--;
}

int retrieve(List *list, int index)
{
    Node *head = list->head;
    if (head == NULL || index > list->count || index < 0)
    {
        return -1;
    }

    Node *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->data;
}

int locate(List *list, int data)
{
    Node *head = list->head;
    if (head == NULL)
    {
        return -1;
    }

    Node *current = head;
    int index = 0;
    while (current != NULL)
    {
        if (current->data == data)
            return index;

        current = current->next;
        index++;
    }

    return -1;
}

void display(List *list)
{
    Node *current = list->head;
    printf("head: ");
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\ncount: %d\n\n", list->count);
}