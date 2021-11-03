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
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<utility>
#include<set>
#include<list>
#include<forward_list>
#include<limits>
using namespace std;
const int N=500,M=100000;
struct egde{
    int from;
    int to;
    int cost;
    int capacity=__INT_MAX__;//容量
    egde *next=NULL;//下一条边
    egde *reverse=NULL;//反向边
}e[M*2+N*(N+1)];//原始边可能有M条，每两台路由器之间可能拆出n(n+1)/2条，再加上每条边的反向边；
int tail;//边表的队尾索引
egde *graph[2*N+1];//1台路由器可能需要拆成2个点；
int vomit[N+1];//路由器的吞吐量
int marked[2*N+1];
long long dist[N+1];
struct comp{
    bool operator()(const egde* a,const egde* b){
        return dist[a->to]>dist[b->to];
    }
};
void add_egde(int from,int to,int cost){
    e[tail].from=from;
    e[tail].to=to;
    e[tail].cost=cost;
    e[tail].next=graph[from];
    graph[from]=&e[tail];
    tail++;
}
void Dijkstra(int begin){
    priority_queue<egde*,vector<egde*>,comp> pq;
    dist[begin]=0;
    for(auto p=graph[begin];p!=NULL;p=p->next){
        dist[p->to]=p->cost;
        pq.push(p);
    }
    while(!pq.empty()){
        egde *current=pq.top();
        pq.pop();
        for(auto p=graph[current->to];p!=NULL;p=p->next){
            if(dist[p->from]+p->cost<dist[p->to]){
                dist[p->to]=dist[p->from]+p->cost;
                pq.push(p);
            }
        }
    }
}
void residual(int begin){//广度优先遍历，构造初始的残存网络
    queue<egde*> q;
    for(auto p=graph[begin];p!=NULL;p=p->next){
        q.push(p);
    }
    while(!q.empty()){
        egde *current=q.front();
        q.pop();
        for(auto p=graph[current->to];p!=NULL;p=p->next){
            if(dist[p->from]+p->cost==dist[p->to]){
                add_egde(p->to,p->from,__INT_MAX__);
                e[tail].reverse=p;
                p->reverse=&e[tail];
                q.push(p);
            }else
                p->capacity=0;
        }
    }

}
/*
void splitvertex(int s,int t,int length){
    for(int i=1;i<=length;i++){
        if(i!=s&&i!=t){//除了起点和终点
            graph[length+i].adjoin.swap(graph[i].adjoin);
            for(auto p=graph[length+i].adjoin.begin();p!=graph[length+i].adjoin.end();p++){
                p->from=length+i;
            }
            graph[i].adjoin.push_front(egde(i,length+i,0,vomit[i]));
            graph[length+i].adjoin.push_front(egde(length+i,i,false));
            graph[i].adjoin.begin()->rev=graph[length+i].adjoin.begin();
            graph[length+i].adjoin.begin()->rev=graph[i].adjoin.begin();
        }
    }

}
void update(int s,int t,int cf){
    int current=t;
    while(current!=s){
        if(path[current]->original){
            path[current]->capacity-=cf;
            path[current]->flow+=cf;
            path[current]->rev->capacity=path[current]->flow;
            path[current]->rev->flow=0;
        }else{
            path[current]->rev->capacity+=cf;
            path[current]->rev->flow-=cf;
            path[current]->capacity=path[current]->rev->flow;
            path[current]->flow=0;
        }
        current=path[current]->from;
    }
}
int bfs(int s,int t){
    queue<int> q;
    int cf=1e9;//残存容量
    memset(marked,0,sizeof(int)*(2*N+1));
    memset(path,0,sizeof(list<egde>::iterator)*(2*N+1));
    marked[s]=1;
    q.push(s);
    while(!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
        for(auto p=graph[current].adjoin.begin();p!=graph[current].adjoin.end();p++){
            if(p->capacity>0&&marked[p->to]==0){
                marked[p->to]=1;
                path[p->to]=p;
                q.push(p->to);
                if(cf>p->capacity)
                    cf=p->capacity;

            }
        }
    }
    if(marked[t]==1){
        update(s,t,cf);
        return cf;
    }else
        return 0;
}
*/
int main(){
    int n,m;
    int v,w,c;
    tail=0;//边表的队尾索引
    unsigned long long maxflow=0;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>v>>w>>c;
        add_egde(v,w,c);
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=__LONG_LONG_MAX__;//顺便把dist初始化了
    }
    Dijkstra(1);
    residual(1);
    for(int i=0;i<tail;i++){
        cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].cost<<" "<<e[i].capacity<<endl;
    }
    cout<<endl;
    /*
    splitvertex(1,n,n);
    while(bfs(1,n));
    for(auto p=graph[1].adjoin.begin();p!=graph[1].adjoin.end();p++){
        maxflow+=p->flow;
    }
    cout<<maxflow<<endl;
    */
    /*
    for(int i=1;i<2*N+1;i++){
        if(!graph[i].adjoin.empty()){
            for(auto e=graph[i].adjoin.begin();e!=graph[i].adjoin.end();e++){
                cout<<"("<<e->from<<","<<e->to<<")={"<<e->capacity<<","<<e->flow<<"} ";
            }
            cout<<endl;
        }
    }
    */
}