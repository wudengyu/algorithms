/*洛谷 P3171 [CQOI2015]网络吞吐量
 *题目背景
 *路由是指通过计算机网络把信息从源地址传输到目的地址的活动，也是计算机网络设计中的重点和难点。网络中实现路由转发的硬件设备称为路由器。为了使数据包最快的到达目的地，路由器需要选择最优的路径转发数据包。例如在常用的路由算法 OSPF (开放式最短路径优先) 中，路由器会使用经典的 Dijkstra 算法计算最短路径，然后尽量沿最短路径转发数据包。
 *题目描述
 *现在，若已知一个计算机网络中各路由器间的连接情况，以及各个路由器的最大吞吐量（即每秒能转发的数据包数量），网络中的路由器使用1到n编号，假设所有数据包一定沿最短路径转发，试计算从路由器1到路由器n的网络的最大吞吐量。计算中忽略转发及传输的时间开销，不考虑链路的带宽限制，即认为数据包可以瞬间通过网络。路由器1到路由器n作为起点和终点，自身的吞吐量不用考虑，网络上也不存在将1和n直接相连的链路。
 *输入格式
 *输入的第一行是用空格隔开的两个整数，分别代表路由器的数量n和链路的数量m。
 *第2到第(m+1)行，每行三个整数u,v,w，代表存在一条连结路由器u和路由器v的距离为w的双向链路。
 *第(m+2)到第(n+m+1)行，每行一个整数，第 (i+m+1)行的整数代表路由器i的吞吐量c_i。
 *输出格式
 *输出一行一个整数，代表网络的最大吞吐量。
*/
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;
const int N=500,M=100000;
struct edge{
    int from;
    int to;
    int cost;
    int capacity=__INT_MAX__;//容量
    edge *next=NULL;//下一条边
    edge *reverse=NULL;//反向边
}e[M*2+N*(N+1)];//原始边可能有M条，每两台路由器之间可能拆出n(n+1)/2条，再加上每条边的反向边；
int tail;//边表的尾后索引
edge *graph[2*N+1];//1台路由器可能需要拆成2个点；N+i对应i拆分出来的点
int vomit[N+1];//路由器的吞吐量
int marked[N+1];
long long dist[N+1];
struct comp{
    bool operator()(const int a,const int b){
        return dist[a]>dist[b];
    }
};
void add_twowayedge(int from,int to,int cost){
    e[tail].from=from;
    e[tail].to=to;
    e[tail].cost=cost;
    e[tail].next=graph[from];
    graph[from]=&e[tail];
    tail++;
    e[tail].from=to;
    e[tail].to=from;
    e[tail].cost=cost;
    e[tail].next=graph[to];
    graph[to]=&e[tail];
    e[tail-1].reverse=&e[tail];
    e[tail].reverse=&e[tail-1];
    tail++;
}
void Dijkstra(int begin){
    priority_queue<int,vector<int>,comp> pq;
    dist[begin]=0;
    pq.push(begin);
    while(!pq.empty()){
        int current=pq.top();
        pq.pop();
        for(auto p=graph[current];p!=NULL;p=p->next){
            if(dist[p->from]+p->cost<dist[p->to]){
                dist[p->to]=dist[p->from]+p->cost;
                pq.push(p->to);
            }
        }
    }
}
//广度优先遍历，初始化残存网络，同时标记最短路径上的顶点
void residual(int begin){
    queue<int> q;
    q.push(begin);
    memset(marked,0,sizeof(int)*(N+1));
    while(!q.empty()){
        int current=q.front();
        q.pop();
        for(auto p=graph[current];p!=NULL;p=p->next){
            if(dist[p->from]+p->cost==dist[p->to]){
                p->capacity=1000000000;
                marked[p->to]=1;
                q.push(p->to);
            }else{
                p->capacity=0;
            }
        }
    }
}
/*拆分之前标记的在最短路径上的点*/
void splitvertex(int begin,int end){
    for(int i=2;i<end;i++){
        if(marked[i]){
            for(auto p=graph[i];p!=NULL;p=p->next)
                p->from=i+N;
            graph[i+N]=graph[i];
            graph[i]=NULL;
            add_twowayedge(i,i+N,0);
            graph[i]->capacity=vomit[i];
            graph[i+N]->capacity=0;
        }
    }
}
/*延路径调整残余流量*/
void update(int s,int t,edge *path[],int cf){
    int current=t;
    while(current!=s){
        path[current]->capacity-=cf;
        path[current]->reverse->capacity+=cf;
        current=path[current]->from;
    }
}
/*基本的Ford-Fulkerson算法*/
int maxflow(int s,int t){
    int cf[2*N+1]; //当前寻路过程中，到达顶点的最小残余流量
    edge* path[2*N+1];//到达节点的边的指针
    int marked[2*N+1]={};
    cf[s]=1000000000;
    marked[s]=1;
    queue<int> q;
    q.push(s);
    if(s==t)
        return 0;
    while(!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
        for(auto p=graph[current];p!=NULL;p=p->next){
            if(marked[p->to]==0&&p->capacity>0){
                marked[p->to]=1;
                path[p->to]=p;
                cf[p->to]=min(cf[current],p->capacity);
                q.push(p->to);
            }
        }
    }
    if(marked[t]==1){
        update(s,t,path,cf[t]);
        return 1;
    }else
        return 0;
}
int main(){
    int n,m;
    int v,w,c;
    tail=0;//边表的尾后索引
    unsigned long long ans=0;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>v>>w>>c;
        add_twowayedge(v,w,c);
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=__LONG_LONG_MAX__;//顺便把dist初始化了
    }
    Dijkstra(1);
    residual(1);
    splitvertex(1,n);
    maxflow(1,n);
    for(int i=0;i<tail;i++){
        cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].cost<<" "<<e[i].capacity<<endl;
    }
    cout<<endl;
}