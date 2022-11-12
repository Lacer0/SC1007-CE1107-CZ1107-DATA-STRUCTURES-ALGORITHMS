#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot)
{
	int p, size;
	p = size = 0;
	ListNode *front, *mid, *back, *WhyIsSizeNotGiven, *cur, *pre, *temp;
	front = mid = back = WhyIsSizeNotGiven = cur = pre = *head;
	while (WhyIsSizeNotGiven != NULL)
	{
		WhyIsSizeNotGiven = WhyIsSizeNotGiven->next;
		size++;
	}
	while (back->next != NULL)
		back = back->next;
	while (mid != NULL)
    {
        if (mid->item == pivot)
            break;
        mid = mid->next;
    }
	for (int i=0; i<size; i++)
	{
	    if (size == 1)
            break;
		if (cur->item < pivot)
		{
			if (p)
			{
                temp = cur->next;
				pre->next = cur->next;
				if (front == mid)
				{
					cur->next = *head;
					*head = front = cur;
				}
				else
				{
					cur->next = front->next;
					front->next = cur;
					front = front->next;
				}
					cur = temp;
			}
			else
			{
			    if (front != cur)
                    front = front->next;
				cur = cur->next;
			}
		}
		else if (cur->item > pivot)
		{
			if (cur == *head)
			{
				temp = cur->next;
				cur->next = NULL;
				back->next = cur;
				back = back->next;
				*head = front = cur = pre = temp;
			}
			else if (cur->next != NULL)
			{
				temp = cur->next;
				pre->next = cur->next;
				cur->next = NULL;
				back->next = cur;
				back = back->next;
				cur = temp;
			}
		}
		else if (cur->item == pivot)
		{
			p = 1;
			cur = cur->next;
		}
		if (cur != NULL)
        {
            if (pre->next->next == cur)
                pre = pre->next;
        }
	}
}
