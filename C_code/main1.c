#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
/* { 
    char *t;
    t=(char *)malloc(sizeof(char)*10);
    printf("no1 strlen(t)=%d   sizeof(t)=%d   \n\n\n",strlen(t),sizeof(t));
    *(t+3)='\0';
    printf("no2 strlen(t)=%d   sizeof(t)=%d   \n",strlen(t),sizeof(t));
    return 0;
} */
{
    char *t=(char *)malloc(sizeof(char)*9);
    // t=(char *)malloc(sizeof(char)*9);
    printf("%d\t%d",strlen(t),sizeof(t));
    return 0;
}