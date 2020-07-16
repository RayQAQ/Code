
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
};


struct Node* InitList()
{
	struct Node *ListHead;
    ListHead = (struct Node *)malloc(sizeof(struct Node));
    ListHead->prev = NULL;
    ListHead->next = NULL;
	return ListHead;
}

int NodeAdd(struct Node *ListHead, void *DataInsert, int sum)
{
    struct Node *NodeNew;
    NodeNew = (struct Node *)malloc(sizeof(struct Node));
    NodeNew->data = DataInsert;
    NodeNew->prev = ListHead;
    NodeNew->next = ListHead->next;
    ListHead->next = NodeNew;
    sum++;
    return sum;
}

int NodeDelet(struct Node *NodeDel, int sum)
{
	if(sum==0)
	{
		return 0;
	}
	if(NodeDel->next)
	{
		//printf("1");
		NodeDel->prev->next = NodeDel->next;
	}
	if(!(NodeDel->next))
	{
		NodeDel->prev->next = NodeDel->next;
    	NodeDel->next->prev = NodeDel->prev;
	}
    
    free(NodeDel);
    sum--;
    return sum;
}

int main()
{
    int sum = 0;
    int DataExample = 2;
	int *DataPtr=&DataExample;
    struct Node *ListHead;
	ListHead = (struct Node *)malloc(sizeof(struct Node));
    ListHead=InitList();
    sum=NodeAdd(ListHead, DataPtr, sum);
	printf("\n%d\n",*(int*)(ListHead->next->data));
	sum=NodeDelet(ListHead->next, sum);
    printf("\n%d\n",sum);
    return 0;
}