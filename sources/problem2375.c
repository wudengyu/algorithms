#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    int value;
    struct vertex* next;
}VERTEX;
int main(){
    int n,m;
    VERTEX graph[100000];
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        graph[i].value=i;
        graph[i].next=NULL;
    }
    while(m--){
        int a,b;
        VERTEX * new;
        scanf("%d%d",&a,&b);
        new=(VERTEX *)malloc(sizeof(VERTEX));
        new->value=b;
        new->next=graph[a].next;
        graph[a].next=new;
    }

    return 0;
}