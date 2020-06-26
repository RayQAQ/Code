#include <stdio.h>
#include <stdlib.h>

//定义结构体Node以及结构体指针SList
typedef struct node
{
        int value;
        struct node *next;
}Node,*SList;

//头插法建立具有头结点的单链表
SList HeadInsert(SList L)
{
    int x,i=1;
    SList temp;
    scanf("%d",&x);
    L = (SList)malloc(sizeof(Node));
    L->value = NULL;
    L->next = NULL;
    while(i<7)
    {
        temp = (SList)malloc(sizeof(Node));
        scanf("%d",&x);
        temp->value = x;
        L->next = temp;
        temp->next = L->next;
    }
}
int main()
{
    
    return 0;
}
