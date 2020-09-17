#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define N 100000 + 1
typedef struct node
{
    int id;
    int cost;
    struct node *next;
} NODE;
NODE *tree[N],queue;
int depth[N],dist[N];
int main(){
    int T, n, p, s, t, u, v, w;
    scanf("%d", &T);
    while (--T){
        scanf("%d%d%d%d", &n, &p, &s, &t);
        for(int i=1;i<=n;i++){//初始化，包括树和距离表
            tree[i]=NULL;
            dist[i]=-1;
        }
        for (int i = 0; i < n - 1; i++){
            scanf("%d%d%d", &u, &v, &w);
            NODE *temp = (NODE *)malloc(sizeof(NODE));
            temp->id = v;
            temp->cost = w;
            temp->next = tree[u];
            tree[u] = temp;
        }
        depth[1]=0;//1号节点是根节点，深度为0
        for(int i=1;i<=n;i++){
            NODE *temp=tree[i];
            while(temp!=NULL){
                depth[temp->id]=depth[i]+1;
                temp=temp->next;
            }
        }
    }
}