#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

#include <ctype.h>

void createExpTree(BTNode** root,char* prefix)
{
    int num = 0;
    while (*prefix == ' ')
        memmove(prefix, prefix+1, strlen(prefix));
    if (*root == NULL)
    {
        *root = malloc(sizeof(BTNode));
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    if (isdigit(*prefix))
    {
        while (*prefix != ' ')
        {
            num *= 10;
            num += ((int) (*prefix)) - 48;
            if (strlen(prefix) == 1)
            {
                (*root)->item = num;
                return;
            }
            memmove(prefix, prefix+1, strlen(prefix));
        }
        (*root)->item = num;
        return;
    }
    else
    {
        (*root)->item = ((int) *prefix) + 99999;
        memmove(prefix, prefix+1, strlen(prefix));
        createExpTree(&(*root)->left, prefix);
        createExpTree(&(*root)->right, prefix);
        return;
    }
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;
    printTree(node->left);
    if (node->item == 42 + 99999)
        printf("%c ", '*');
    else if (node->item == 43 + 99999)
        printf("%c ", '+');
    else if (node->item == 45 + 99999)
        printf("%c ", '-');
    else if (node->item == 47 + 99999)
        printf("%c ", '/');
    else
        printf("%d ", node->item);
    printTree(node->right);
}


void printTreePostfix(BTNode *node)
{
    if (node == NULL)
        return;
    printTreePostfix(node->left);
    printTreePostfix(node->right);
    if (node->item == 42 + 99999)
        printf("%c ", '*');
    else if (node->item == 43 + 99999)
        printf("%c ", '+');
    else if (node->item == 45 + 99999)
        printf("%c ", '-');
    else if (node->item == 47 + 99999)
        printf("%c ", '/');
    else
        printf("%d ", node->item);
}

double computeTree(BTNode *node)
{
    double l, r;
    if (node == NULL)
        return 0;
    l = computeTree(node->left);
    r = computeTree(node->right);
    if (node->item == 42 + 99999)
        return (l * r);
    else if (node->item == 43 + 99999)
        return (l + r);
    else if (node->item == 45 + 99999)
        return (l - r);
    else if (node->item == 47 + 99999)
        return (l / r);
    else
        return node->item;
}

//BTNode *newnode(char item){
//    BTNode *temp = malloc(sizeof(BTNode));
//    temp->item = item; temp->left=NULL; temp->right = NULL;
//    return temp;
//}
//
//void createExpTree(BTNode** root,char* prefix)
//{
//    Stack *s = malloc(sizeof(Stack)); s->size=0; s->head=NULL;
//
//    int i=0;
//    int n=0;
//    char c;
//    BTNode *curr,*left,*right;
//    while (prefix[i]!='\0'){
//        c = prefix[i];
//        if (*root==NULL)
//            {*root=newnode(c);
//            push(s,*root);}
//
//        switch(c){
//        case '*':
//        case '+':
//        case '-':
//        case '/':
//
//        // insert into tree
//
//        curr = peek(*s); pop(s);
//        curr->item=c;
//
//        left = newnode(1); curr->left = left;
//        right = newnode(1); curr->right = right;
//
//        push(s, right);
//        push(s, left);
//        break;
//
//        case ' ':
//        break;
//
//
//        default: //operand
//        n=0;
//        while (prefix[i] !=' ' && prefix[i] !='\0'){
//
//            n = n*10 + (prefix[i]-'0');
//            i++;
//            }
//            curr = peek(*s); pop(s);
//            curr->item = n;
//        }
//
//if (prefix[i]=='\0') return;
//i++;
//
//    }
// //Write your code here
//
//}
//
//void printTree(BTNode *node){
//
//    if (node==NULL) return;
//
//    //Write your code here
//    if (node->left==NULL){ // no more shit
//        printf("%d", (node->item));
//        return;
//    }
//    printTree(node->left);
//    printf(" %c ", (node->item));
//    printTree(node->right);
//
//}
//
//
//void printTreePostfix(BTNode *node){
//
//    if (node==NULL) return;
//
//      //Write your code here
//    if (node->left==NULL){ // no more shit
//        printf("%d ", (node->item));
//        return;
//    }
//    printTreePostfix(node->left);
//    printTreePostfix(node->right);
//    printf("%c ", (node->item));
//
//}
//
//double computeTree(BTNode *node){
//
//    //Write your code here
//    char c = node->item;
//    if (node->left==NULL) return ((double) node->item); // shits number
//    switch(c){
//        case '*':
//        return (computeTree(node->left) * computeTree(node->right));
//        break;
//        case '+':
//        return (computeTree(node->left) + computeTree(node->right));
//        break;
//        case '-':
//        return (computeTree(node->left) - computeTree(node->right));
//        break;
//        case '/':
//        return (computeTree(node->left) / computeTree(node->right));
//        break;
//    }
//}
