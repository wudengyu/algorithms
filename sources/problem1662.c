#include <stdio.h>
#include <stdlib.h>
typedef struct vertex{
    int value;
    struct vertex* next;
}Vertex;
Vertex tree[6001];
int indegree[6001]={0};//记录节点入度，用来找老白兔的。  
int dp[6001][2];
int solve(int i){
    Vertex* child;
    dp[i][0]=0;
    dp[i][1]=tree[i].value;
    while(tree[i].next!=NULL){
        child=tree[i].next;
        dp[i][0]+=solve(child->value);
        dp[i][1]+=dp[child->value][0];
        tree[i].next=child->next;
        free(child);
    }
    return dp[i][0]>dp[i][1]?dp[i][0]:dp[i][1];
}
int main(){
    int n,l,k;
    Vertex* new;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&tree[i].value);
        tree[i].next=NULL;
    }
    while(1){
        scanf("%d%d",&l,&k);
        if(l==0||k==0) break;
        new=(Vertex*)malloc(sizeof(Vertex));
        new->value=l;
        new->next=tree[k].next;
        tree[k].next=new;
        indegree[l]++;
    }
    for(int i=1;i<=n;i++){
        if(!indegree[i])
            printf("%d\n",solve(i));
    }
}