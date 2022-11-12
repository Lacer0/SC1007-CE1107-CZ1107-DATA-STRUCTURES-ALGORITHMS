#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

#include <math.h>
#include <ctype.h>

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    Stack oper;
    oper.head = NULL;
    oper.size = 0;
    char revInfix[SIZE];
    char revPrefix[SIZE];
    char c;
    char n[SIZE];
    int d, j, k, count, sum;
    d = j = k = count = sum = 0;
    while (infix[count] != '\0')
        count++;
    for (int i=count-1; i>=0; i--)
        revInfix[count-1-i] = infix[i];
    revInfix[count]='\0';
    while (j < SIZE && revInfix[j] != '\0')
    {
        c = revInfix[j++];
        switch(c)
        {
            case '*':
            case '/':
            case '+':
            case '-':
                while ((!isEmptyStack(oper) && peek(oper) != '(' && (((int)(peek(oper)) == 42 || (int)(peek(oper)) == 47) && ((int)(c) == 43 || (int)(c) == 45))))
                {
                    revPrefix[k++] = peek(oper);
                    pop(&oper);
                }
                push(&oper, c);
                break;
            case ')':
                push(&oper, c);
                break;
            case '(':
                while (!isEmptyStack(oper))
                {
                    if (peek(oper) != ')')
                    {
                        revPrefix[k++] = peek(oper);
                        pop(&oper);
                    }
                    else
                    {
                        pop(&oper);
                        break;
                    }
                }
                break;
            default:
                revPrefix[k++] = c;
                if (!isdigit(revInfix[j]))
                    revPrefix[k++] = '?';
        }
    }
    while (!isEmptyStack(oper))
    {
        revPrefix[k++] = peek(oper);
        pop(&oper);
    }
    revPrefix[k] = '\0';
    count = 0;
    while (revPrefix[count] != '\0')
        count++;
    for (int i=0; i<count; i++)
    {
        if (revPrefix[i] == '?')
            continue;
        if (isdigit(revPrefix[i]))
        {
            if (isdigit(revPrefix[i+1]))
            {
                n[d++] = revPrefix[i];
            }
            else
            {
                n[d++] = revPrefix[i];
                n[d] = '\0';
                sum = 0;
                for (int m=0; m<d; m++)
                {
                    sum += ((int)(n[m]) - 48) * pow(10, m);
                }
                insertNode(inExpLL, sum, OPERAND);
                d = 0;
            }
        }
        else
            insertNode(inExpLL, (int)(revPrefix[i]), OPT);
    }
}
