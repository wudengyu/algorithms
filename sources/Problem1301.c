#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#define N 100000 + 1
typedef struct node{
    int id;
    int cost;
    struct node *next;
} NODE;
NODE *tree[N];
int depth[N],dist[N],queue[N],visited[N];
void min_heapify(int a[],int length,int i){
    int l=2*i,r=2*i+1,min,temp;
    if(l<=length&&dist[a[i]]>dist[a[l]])
        min=l;
    else
        min=i;
    if(r<=length&&dist[a[min]]>dist[a[r]])
        min = r;
    if(min!=i){
        temp=a[i];
        a[i]=a[min];
        a[min]=temp;
        min_heapify(a,length,min);
    }
}
void build_min_heap(int a[],int length){
    for(int i=length/2;i>=1;i--)
        min_heapify(a,length,i);
}
int main(){
    int T, n, p, s, t, u, v, w;
    scanf("%d", &T);
    while (--T){
        scanf("%d%d%d%d", &n, &p, &s, &t);
        for(int i=1;i<=n;i++){//初始化，包括树、距离表和已经访问过的节点
            tree[i]=NULL;
            dist[i]=INT_MAX;
            visited[i]=0;
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
        dist[1]=0;
        queue[0]=1;//队列长度
        queue[1]=1;
        while(queue[0]!=0){
            int current=queue[1];
            visited[current]=1;
        }
    }
}