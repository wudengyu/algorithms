#include <stdio.h>
#include <stdlib.h>
typedef struct vertex{
    int value;
    struct vertex* next;
}Vertex;
Vertex tree[6000];
short indegree[6000]={0};//记录节点入度，用来找老白兔的。  
short dp[6000][2];
int solve(int i){
    if(tree[i].next==NULL){
        dp[i][0]=0;
        dp[i][1]=tree[i].value;
    }else{
        
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
            printf("root is %d\n",i);
    }

}