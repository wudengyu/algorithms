#include <stdio.h>
#include <stdlib.h>
struct node{
    unsigned long long a;
    unsigned long long p;
}tower[200000];
int comp(const void * x,const void * y){
    if(((struct node *)x)->a!=((struct node *)y)->a)
        return ((struct node *)x)->a-((struct node *)y)->a;
    else
        return ((struct node *)x)->p-((struct node *)y)->p;
}
int main(){
    int n,s=0;
    unsigned long long ai,pi,cost=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&tower[i].a,&tower[i].p);
    }
    qsort(tower,n,sizeof(struct node),comp);
    ai=tower[0].a;
    pi=tower[0].p;
    while(s<n-1){
        s++;
        if(tower[s].p<pi||s==n-1){
            cost+=(tower[s].a-ai)*pi;
            ai=tower[s].a;
            pi=tower[s].p;
        }
    }
    printf("%llu\n",cost);
}