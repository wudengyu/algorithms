#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#define N 100000 + 1
typedef struct edge{
    int to;
    int cost;
    int next;
}Edge;
typedef struct vertex{
    int from;
    int depth;
    unsigned long long dist;
    int adj;
}Vetrex;
Vetrex vertexs[3*N];//顶点数最多3*N，1~N用来保存树的节点，N+1~2N用来保存附加的上行中转节点，2N+1~3N用来保存附加的下行中转节点
Edge edges[5*N];//最大边数5*N
int mark[3*N],pq[5*N],len;//pq是顶点的索引的最小优先队列，len为队列实际长度
void swim(int a[],int k){
    while(k>1&&vertexs[a[k/2]].dist>vertexs[a[k]].dist){
        int temp=a[k/2];
        a[k]=a[k/2];
        a[k/2]=temp;
        k/=2;
    }
}
void sink(int a[],int len,int k){
    while(2*k<=len){
        int j=2*k;
        if(j<len&&vertexs[a[j]].dist>vertexs[a[j+1]].dist)j++;
        if(vertexs[a[k]].dist<vertexs[a[j]].dist)break;
        int temp=a[k];
        a[k]=a[j];
        a[j]=temp;
        k=j;
    }
}
int dfs(Vetrex a[],int id){
    int temp=a[id].adj;
    int d=a[id].depth,maxd=0;
    while(temp!=-1){
        a[edges[temp].to].depth=d+1;
        int m=dfs(a,edges[temp].to);
        temp=edges[temp].next;
        maxd=maxd>m?maxd:m;
    }
    return maxd>d?maxd:d;
}
void enqueue(int a[],int *len,int value){
    (*len)++;
    a[*len]=value;
    swim(a,*len);
}
int dequeue(int a[],int *len){
    int temp=a[1];
    a[1]=a[(*len)--];
    if(*len<0)return -1;
    sink(a,*len,1);
    return temp;
}
int main(){
    int T, n, p, s, t, u, v, w;
    int maxdepth;
    scanf("%d", &T);
    for(int c=1;c<=T;c++){
        scanf("%d%d%d%d",&n,&p,&s,&t);
        for(int i=1;i<=n;i++){//初始化树和标志数组
            vertexs[i].adj=-1;
            vertexs[i].depth=0;
            vertexs[i].dist=__LONG_LONG_MAX__;
            mark[i]=0;
        }
        for (int i = 0; i < n - 1; i++){
            scanf("%d%d%d", &u, &v, &w);
            edges[i].to = v;
            edges[i].cost = w;
            edges[i].next = vertexs[u].adj;
            vertexs[u].adj = i;
        }
        maxdepth=dfs(vertexs,1);//深度优先算法计算每个树节点的深度，返回树的高度
        for(int i=1;i<=n;i++){//初始化附加的点及其标记数组中的值，主要是确保邻接边指向空
            vertexs[N+i].adj=-1;
            vertexs[N+i].dist=__LONG_LONG_MAX__;
            vertexs[2*N+i].adj=-1;
            vertexs[2*N+i].dist=__LONG_LONG_MAX__;
            mark[N+i]=0;
            mark[2*N+i]=0;
        }
        for(int i=1;i<=n;i++){//遍历树节点，根据每个节点的深度，添加到中间节点的上行和下行边；
            if(vertexs[i].depth>0){
                edges[N+i].to=2*N+vertexs[i].depth;
                edges[N+i].cost=p/2;
                edges[N+i].next=vertexs[i].adj;
                vertexs[i].adj=N+i;
                edges[2*N+i].to=i;
                edges[2*N+i].cost=p-p/2;
                edges[2*N+i].next=vertexs[N+vertexs[i].depth].adj;
                vertexs[N+vertexs[i].depth].adj=2*N+i;
            }
            if(vertexs[i].depth<maxdepth){
                edges[3*N+i].to=N+vertexs[i].depth+1;
                edges[3*N+i].cost=p/2;
                edges[3*N+i].next=vertexs[i].adj;
                vertexs[i].adj=3*N+i;
                edges[4*N+i].to=i;
                edges[4*N+i].cost=p-p/2;
                edges[4*N+i].next=vertexs[2*N+vertexs[i].depth+1].adj;
                vertexs[2*N+vertexs[i].depth+1].adj=4*N+i;
            }
        }
        //dijkstra(vertexs,s,t);
        len=1;//队列长度
        pq[1]=s;//起始节点是s
        vertexs[s].dist=0;
        vertexs[s].from=s;
        while(len>0){
            int current=0;
            do{
                current=dequeue(pq,&len);//取出最小节点
            }while(mark[current]==1&&current!=-1);
            if(current==t||current==-1)break;
            mark[current]=1;//标记
            int adj=vertexs[current].adj;
            while(adj!=-1){
                int w=edges[adj].to;
                if(vertexs[w].dist>vertexs[current].dist+edges[adj].cost){
                    vertexs[w].dist=vertexs[current].dist+edges[adj].cost;
                    vertexs[w].from=current;
                    enqueue(pq,&len,w);
                    printf("-----");
                }
                printf("V[%d] from %d,dist=%llu\n",w,current,vertexs[w].dist);
                adj=edges[adj].next;
            }
        }
        printf("Case #%d: %llu\n",c,vertexs[t].dist);
    }
}