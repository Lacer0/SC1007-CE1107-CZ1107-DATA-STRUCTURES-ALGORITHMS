#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}

int numMountainPairs(CDblLinkedList CDLL)
{
    CDblListNode *currX, *currY;
    int pair, x, y, mount, s, b;
    int index[300][300] = {0}; //Adjust until pass
    pair = mount = 0;
    currX = CDLL.head;
    for (int i=0; i<CDLL.size; i++)
    {
        x = currX->item;
        currY = currX->next;
        mount = 0;
        for (int j=1; j<CDLL.size; j++)
        {
            y = currY->item;
            if (y >= mount)
            {
                s = (i < (i+j)%CDLL.size) ? i : (i+j)%CDLL.size;
                b = (i > (i+j)%CDLL.size) ? i : (i+j)%CDLL.size;
                if (!index[s][b])
                {
                    index[s][b] = 1;
                    pair++;
                }
                mount = (y > mount) ? y : mount;
            }
            if (mount > x)
                break;
            currY = currY->next;
        }
        currY = currX->pre;
        mount = 0;
        for (int k=1; k<CDLL.size; k++)
        {
            y = currY->item;
            if (y >= mount)
            {
                s = (i < (i-k+CDLL.size)%CDLL.size) ? i : (i-k+CDLL.size)%CDLL.size;
                b = (i > (i-k+CDLL.size)%CDLL.size) ? i : (i-k+CDLL.size)%CDLL.size;
                if (!index[s][b])
                {
                    index[s][b] = 1;
                    pair++;
                }
                mount = (y > mount) ? y : mount;
            }
            if (mount > x)
                break;
            currY = currY->pre;
        }
        currX = currX->next;
    }
    return pair;
}
