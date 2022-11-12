#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode{
	BTNode *data;
	struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

BTNode* findLargestBST (BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");
    printf("The input binary tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    BTNode* BSTnode = findLargestBST (root);
    printf("The largest binary search subtree:\n");
    if(BSTnode)
        printBTNode(BSTnode,0,0);
    else
        printf("No BST\n");
    deleteTree(&root);

    return 0;
}

BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

//BTNode* isSubTree (BTNode* node)
//{
//    int notsubTree = 0;
//    if (node->left)
//    {
//        if (node->left->left == NULL && node->left->right == NULL) ;
//        else
//            notsubTree = 1;
//    }
//    if (node->right)
//    {
//        if (node->right->left == NULL && node->right->right == NULL) ;
//        else
//            notsubTree = 1;
//    }
//    if (!notsubTree)
//        return node;
//    return NULL;
//}
//
//BTNode* findLargestBST (BTNode* root)
//{
//    static int leaf = 0;
//    static int first = 0;
//    BTNode *l, *r;
//    if (!first && isSubTree(root))
//        return NULL;
//    first = 1;
//    if (root == NULL)
//        return NULL;
//    if (root->left == NULL && root->right == NULL)
//    {
//        leaf = 1;
//        return root;
//    }
//    l = findLargestBST(root->left);
//    r = findLargestBST(root->right);
//    if (leaf)
//    {
//        leaf = 0;
//        if (isSubTree(root))
//            return root;
//    }
//    if (l == NULL)
//        return r;
//    if (r == NULL)
//        return l;
//    if ((l->left != NULL) && (l->right != NULL))
//        return l;
//    if ((r->left != NULL) && (r->right != NULL))
//        return r;
//    if ((l->left != NULL) || (l->right != NULL))
//        return l;
//    if ((r->left != NULL) || (r->right != NULL))
//        return r;
//}
int BST(BTNode* node)
{
    static BTNode *prev = NULL;
    if (node)
    {
        if (!BST(node->left))
            return 0;
        if (prev != NULL && node->item <= prev->item)
            return 0;
        prev = node;
        return BST(node->right);
    }
    return 1;
}

int countNode(BTNode* node)
{
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    return countNode(node->left) + countNode(node->right) + 1;
}

BTNode* findLargestBST(BTNode* root)
{
    BTNode *l, *r;
    if (root == NULL)
        return NULL;
    if (root->left == NULL && root->right == NULL)
        return root;
    l = findLargestBST(root->left);
    r = findLargestBST(root->right);
    if (isBST(root))
        return root;
    else if (countNode(l) >= countNode(r))
        return l;
    else
        return r;
}

int isBST(BTNode *root){
    if(root==NULL)
       return 1;

    return isBSTX(root,NULL,NULL);
}

int isBSTX(BTNode *root,BTNode* l, BTNode* r){
    if(root==NULL) return 1;

    if(l!=NULL && root->item <= l->item)
        return 0;
    if(r!=NULL && root->item >= r->item)
        return 0;

    return isBSTX(root->left,l,root) && isBSTX(root->right,root,r);

}
