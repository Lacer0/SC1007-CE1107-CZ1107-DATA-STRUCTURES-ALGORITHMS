#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

#include <string.h>

BTNode *newNode(char item)
{
    BTNode *temp = malloc(sizeof(BTNode));
    temp->id = item;
    temp->left=NULL;
    temp->right = NULL;
    return temp;
}

void buildTree(BTNode** node, char* preO, char* postO)
{
    int preIndex = 0;
    int size = strlen(preO);
    buildbuildTree(&(*node), preO, postO, &preIndex, 0, size - 1, size);
}

void buildbuildTree(BTNode** node, char* preO, char* postO, int* preIndex, int l, int h, int size)
{
    // Base case
    if (*preIndex >= size || l > h)
        return;

    // The first node in preorder traversal is root. So take the node at
    // preIndex from preorder and make it root, and increment preIndex
    *node = malloc(sizeof(BTNode));
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->id = preO[(*preIndex)++];

    // If the current subarray has only one element, no need to recur
    if (l == h)
        return;

    // Search the next element of pre[] in post[]
    int i;
    for (i = l; i <= h; ++i)
        if (preO[*preIndex] == postO[i])
            break;

    // Use the index of element found in postorder to divide
    // postorder array in two parts. Left subtree and right subtree
    if (i <= h)
    {
        buildbuildTree(&(*node)->left, preO, postO, preIndex, l, i, size);
        buildbuildTree(&(*node)->right, preO, postO, preIndex, i+1, h-1, size);
    }

    return;
}
