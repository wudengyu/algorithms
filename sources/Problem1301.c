#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#define N 100000 + 1
typedef struct edge{
    int id;
    int cost;
    struct edge *next;
}Edge;
struct vertex{
    int id;
    int depth;
    long long dist;
    struct edge *adj;
    struct vertex *some;
}tree[N],*depths[N];
int queue[N],len;//len为队列实际长度
int pos[N];//记录节点在队列中的位置
void swim(int a[],int k){
    while(k>1&&tree[a[k/2]].dist>tree[a[k]].dist){
        int temp=a[k/2];
        a[k]=a[k/2];
        a[k/2]=temp;
        pos[a[k]]=k;
        pos[a[k/2]]=k/2;
        k/=2;
    }
}
void sink(int a[],int len,int k){
    while(2*k<=len){
        int j=2*k;
        if(j<len&&tree[a[j]].dist>tree[a[j+1]].dist)j++;
        if(tree[a[k]].dist<tree[a[j]].dist)break;
        int temp=a[k];
        a[k]=a[j];
        a[j]=temp;
        pos[a[k]]=k;
        pos[a[j]]=j;
        k=j;
    }
}
void calcdepth(struct vertex a[],int id){
    Edge* temp=a[id].adj;
    while(temp!=NULL){
        a[temp->id].depth=a[id].depth+1;
        a[temp->id].some=depths[a[temp->id].depth];
        depths[a[temp->id].depth]=&a[temp->id];
        calcdepth(a,temp->id);
        temp=temp->next;
    }
}
int main(){
    int T, n, p, s, t, u, v, w;
    scanf("%d", &T);
    for(int c=1;c<=T;c++){
        scanf("%d%d%d%d",&n,&p,&s,&t);
        for(int i=1;i<=n;i++){//初始化，包括树和节点
            tree[i].id=i;
            tree[i].adj=NULL;
            tree[i].some=NULL;
            tree[i].dist=__LONG_LONG_MAX__;
            depths[i]=NULL;
            pos[i]=0;
        }
        for (int i = 0; i < n - 1; i++){
            scanf("%d%d%d", &u, &v, &w);
            Edge *temp = (Edge *)malloc(sizeof(Edge));
            temp->id = v;
            temp->cost = w;
            temp->next = tree[u].adj;
            tree[u].adj = temp;
        }
        tree[1].depth=0;//1号节点是根节点，深度为0
        depths[0]=&tree[1];
        calcdepth(tree,1);//深度优先算法计算每个节点深度
        
        len=1;//队列长度
        queue[1]=s;//起始节点是s
        tree[s].dist=0;
        while(len>0){
            int current=queue[1];//取出最小节点
            queue[1]=queue[len--];//最后一个节点取出放到第一个节点位置（此时队列可能已经为空）
            if(len>0)
                pos[queue[1]]=1;
            pos[current]=0;
            sink(queue,len,1);//下沉，队列即使为空也无妨
            Edge* adj=tree[current].adj;
            while(adj!=NULL){
                int w=adj->id;
                if(tree[w].dist>tree[current].dist+adj->cost){
                    tree[w].dist=tree[current].dist+adj->cost;
                    if(pos[w])
                        swim(queue,pos[w]);//如果节点已经在队列中，更新距离后可能需要“上浮”
                    else{
                        len++;
                        queue[len]=w;
                        pos[w]=len;
                        swim(queue,len);
                    }
                }
                adj=adj->next;
            }//这个循环处理树中的节点，下一部分处理相邻层次节点，方法是一样的
            /*
            if(tree[current].depth>0){
                struct vertex *so=depths[tree[current].depth-1];
                while(so!=NULL){
                    int w=so->id;
                    if(tree[w].dist>tree[current].dist+p){
                        tree[w].dist=tree[current].dist+p;
                        if(pos[w])
                            swim(queue,pos[w]);//如果节点已经在队列中，更新距离后可能需要“上浮”
                        else{
                            len++;
                            queue[len]=w;
                            pos[w]=len;
                            swim(queue,len);
                        }
                    }
                    so=so->some;
                }
            }
            struct vertex *so=depths[tree[current].depth+1];
            while(so!=NULL){
                int w=so->id;
                if(tree[w].dist>tree[current].dist+p){
                    tree[w].dist=tree[current].dist+p;
                    if(pos[w])
                        swim(queue,pos[w]);//如果节点已经在队列中，更新距离后可能需要“上浮”
                    else{
                        len++;
                        queue[len]=w;
                        pos[w]=len;
                        swim(queue,len);
                    }
                }
                so=so->some;
            }
            */
        }
        printf("Case #%d: %lld",c,tree[t].dist);
    }
}