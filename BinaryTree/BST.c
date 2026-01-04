#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Node
{
    struct Node *lc;
    struct Node *rc;
    int data;
} Node, *BST;

void insert(BST *B, int value)
{
    BST *trav = B;
    while(*trav != NULL && (*trav)->data != value)
    {
        trav = value > (*trav)->data ? &(*trav)->rc : &(*trav)->lc;
    }
    *trav = (BST)calloc(1, sizeof(Node));
    (*trav)->data = value;
}

void delete(BST *B, int value)
{
    BST *trav = B;
    while(*trav != NULL && (*trav)->data != value)
    {
        trav = value < (*trav)->data ? &(*trav)->lc : &(*trav)->rc;
    }
    if(*trav == NULL) 
    {
        printf("\nCould not delete %d, not found", value);
        return;
    }
    BST del = *trav;
    if(del->lc == NULL)
    {
        *trav = del->rc;
        free(del);
    }
    else if(del->rc == NULL)
    {
        *trav = del->lc;
        free(del);
    }
    else
    {
        BST *succ = &del->rc;
        while((*succ)->lc != NULL)
            succ = &(*succ)->lc;
        del->data = (*succ)->data;
        delete(succ, (*succ)->data);
    }
    printf("\nDeleted %d", value);
}

void deleteWithSuccessor(BST *B, int value)
{
    BST *trav = B;
    while(*trav != NULL && (*trav)->data != value)
    {
        trav = value < (*trav)->data ? &(*trav)->lc : &(*trav)->rc;
    }

    if(*trav == NULL)
    {
        printf("\nCould not delete %d, not found", value);
        return;
    }

    BST del = *trav;

    if(del->rc == NULL)
    {
        *trav = del->lc;
        free(del);
    }
    else if(del->lc == NULL)
    {
        *trav = del->rc;
        free(del);
    }
    else
    {
        BST parent = del;
        BST succ = del->rc;
        while(succ->lc != NULL)
        {
            parent = succ;
            succ = succ->lc;
        }

        del->data = succ->data;

        if(parent->rc == succ)
            parent->rc = succ->rc;
        else
            parent->lc = succ->rc;

        free(succ);
    }
    printf("\nDeleted %d", value);
}

void inorder(BST B)
{
    if(B != NULL)
    {
        inorder(B->lc);
        printf("%d ", B->data);
        inorder(B->rc);
    }
}

void preorder(BST B)
{
    if(B != NULL)
    {
        printf("%d ", B->data);
        preorder(B->lc);
        preorder(B->rc);
    }
}

void postorder(BST B)
{
    if(B != NULL)
    {
        postorder(B->lc);
        postorder(B->rc);
        printf("%d ", B->data);
    }
}

void dfs(BST root)
{
    if(!root) return;
    BST queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while(front < rear)
    {
        BST curr = queue[front++];
        printf("%d ", curr->data);
        if(curr->lc != NULL) 
            queue[rear++] = curr->lc;
        if(curr->rc != NULL) 
            queue[rear++] = curr->rc;
    }
}


void inorderIterative(BST root)
{
    BST stack[MAX];
    int top = -1;
    BST curr = root;
    while(curr != NULL || top != -1)
    {
        while(curr != NULL)
        {
            stack[++top] = curr;
            curr = curr->lc;
        }
        curr = stack[top--];
        printf("%d ", curr->data);
        curr = curr->rc;
    }
}

void preorderIterative(BST root)
{
    if(!root) return;
    BST stack[MAX];
    int top = -1;
    stack[++top] = root;
    while(top != -1)
    {
        BST curr = stack[top--];
        printf("%d ", curr->data);
        if(curr->rc != NULL) 
            stack[++top] = curr->rc;
        if(curr->lc != NULL) 
            stack[++top] = curr->lc;
    }
}

void postorderIterative(BST root)
{
    if(!root) return;
    BST s1[MAX], s2[MAX];
    int t1 = -1, t2 = -1;
    s1[++t1] = root;
    while(t1 != -1)
    {
        BST curr = s1[t1--];
        s2[++t2] = curr;
        if(curr->lc != NULL) 
            s1[++t1] = curr->lc;
        if(curr->rc != NULL) 
            s1[++t1] = curr->rc;
    }
    while(t2 != -1)
        printf("%d ", s2[t2--]->data);
}

int main()
{
    BST B = NULL;
    insert(&B, 5);
    insert(&B, 3);
    insert(&B, 10);
    insert(&B, 2);
    insert(&B, 4);
    insert(&B, 9);
    insert(&B, 15);
    printf("Root: %d", B->data);
    printf("\nInorder: ");
    inorder(B);
    delete(&B, 5);
    delete(&B, 67);
    deleteWithSuccessor(&B, 10);
    printf("\nPreorder: ");
    preorder(B);
    printf("\nPostorder: ");
    postorder(B);
    printf("\nDFS: ");
    dfs(B);
    printf("\nIterative Inorder: ");
    inorderIterative(B);
    printf("\nIterative Preorder: ");
    preorderIterative(B);
    printf("\nIterative Postorder: ");
    postorderIterative(B);
    return 0;
}