#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{ 
    char *t;
    t=(char *)calloc(sizeof(char),10);
    printf("no1\tstrlen(t)=%d\tsizeof(t)=%d\n",strlen(t),sizeof(t));
    *(t+3)='\0';
    printf("no2\tstrlen(t)=%d\tsizeof(t)=%d\n",strlen(t),sizeof(t));
    return 0;
}
