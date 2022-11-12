#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
	int i = 0;
	ListNode *pre, *cur, *temp, *check, *seg;
	pre = cur = check = head;
	if (start < 0 || end < 0)
		return head;
	while (check != NULL)
	{
		check = check->next;
		i++;
	}
	if (start > i || end > i)
		return head;
	for (int j=1; start>j; j++)
		pre = pre->next;
	if (start > 0)
	{
		seg = pre;
		pre = pre->next;
		cur = pre->next;
		for (int k=0; end-start>k; k++)
		{
			temp = cur->next;
			cur->next = seg->next;
			seg->next = cur;
			pre->next = temp;
			cur = temp;
		}
	}
	else
	{
		for (int k=0; end+1>k; k++)
		{
			temp = cur->next;
			cur->next = head;
			head = cur;
			pre->next = temp;
			cur = temp;
		}
	}
	return head;
}
