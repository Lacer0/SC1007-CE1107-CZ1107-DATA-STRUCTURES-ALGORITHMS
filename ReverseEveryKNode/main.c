#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K)
{
	int i = K;
	int ignore = 0;
	ListNode *pre, *cur, *temp, *seg, *check;
	pre = cur = seg = *head;
	if (K == 1 || K == 0)
        return;
	while (cur != NULL)
	{
		if (i == K)
		{
			seg = pre;
			if (pre != *head)
				pre = pre->next;
			i = 0;
			check = (seg == *head) ? seg : seg->next;
			for (int n=0; n < K; n++)
			{
				if (check == NULL)
				{
					ignore = 1;
					break;
				}
				check = check->next;
			}
		}
		if (ignore)
			break;
		if (pre == cur)
		{
			cur = cur->next;
		}
		else if (seg == *head)
		{
			temp = cur->next;
			cur->next = *head;
			seg = *head = cur;
			pre->next = temp;
			cur = temp;
		}
		else
		{
			temp = cur->next;
			cur->next = seg->next;
			seg->next = cur;
			pre->next = temp;
			cur = temp;
		}
		i++;
	}
}
