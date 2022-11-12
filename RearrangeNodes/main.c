#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll)
{
	ListNode *left, *right, *temp;
	left = right = ll.head;
	for (int i=0; i<ll.size/2; i++)
	{
		right = right->next;
	}
	if (ll.size == 1)
		return ll;
	else
	{
		ll.head = right;
		for (int i=0; i<ll.size/2; i++)
		{
			temp = left->next;
			left->next = right->next;
			right->next = left;
			left = temp;
			right = right->next->next;
		}
	}

	left = right = ll.head;
	for (int i=0; i<ll.size/2; i++)
	{
		right = right->next;
	}
	for (int i=0; i<ll.size/2; i++)
	{
	    if (i+1 == ll.size/2)
            left->next = right->next;
		temp = right->next;
		right->next = left->next;
		left->next = right;
		right = temp;
		left = left->next->next;
	}
	return ll;
}
