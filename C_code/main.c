#include <stdio.h>
#include <stdlib.h>
#define maxsize 50
struct SqList
{
    int data[maxsize];
    int length;
}SqList,*Z;
int main()
{
    struct SqList L={1,2,3};
    struct SqList *P=&L;
    Z=&L;
    printf("%d\t%d\n", L.data[2], L.length);
    printf("%d\t%d\n", P->data[2], P->length);
    printf("%d\t%d", Z->data[2], Z->length);    
    return 0;
}
