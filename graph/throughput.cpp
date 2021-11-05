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
const long long inf=__LONG_LONG_MAX__;
struct edge{
    int from;
    int to;
    long long value;
    int next=0;//下一条边
}original[M],e[(M+N+2)*2];//原始边可能有M条，每台路由器之间可能拆出1条，再加反向边乘2；
int tail;//边表的尾后索引
int head[2*(N+1)];//1台路由器可能需要拆成2个点；N+i对应i拆分出来的点
int vomit[N+1];//路由器的吞吐量
long long dist[N+1];
long long ans;
struct comp{
    bool operator()(const int a,const int b){
        return dist[a]>dist[b];
    }
};
void add_edge(int from,int to,long long value){
    e[tail].from=from;
    e[tail].to=to;
    e[tail].value=value;
    e[tail].next=head[from];
    head[from]=tail;
    tail++;
}
void Dijkstra(int begin){
    priority_queue<int,vector<int>,comp> pq;
    dist[begin]=0;
    pq.push(begin);
    while(!pq.empty()){
        int current=pq.top();
        pq.pop();
        for(auto p=head[current];p!=0;p=e[p].next){
            if(dist[e[p].from]+e[p].value<dist[e[p].to]){
                dist[e[p].to]=dist[e[p].from]+e[p].value;
                pq.push(e[p].to);
            }
        }
    }
}
/*延路径调整残余流量*/
void update(int s,int t,int path[],int cf){
    int current=t;
    while(current!=s){
        e[path[current]].value-=cf;
        e[path[current]^1].value+=cf;
        current=e[path[current]].from;
    }
    ans+=cf;
}
/*基本的Ford-Fulkerson算法*/
int maxflow(int s,int t){
    long long cf[2*(N+1)]={}; //当前寻路过程中，到达顶点的最小残余流量
    int path[2*(N+1)]={};//到达节点的边的指针
    int marked[2*(N+1)]={};
    cf[s]=inf;
    marked[s]=1;
    queue<int> q;
    q.push(s);
    if(s==t)
        return 0;
    while(!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
        for(auto p=head[current];p!=0;p=e[p].next){
            if(marked[e[p].to]==0&&e[p].value>0){
                marked[e[p].to]=1;
                path[e[p].to]=p;
                cf[e[p].to]=min(cf[current],e[p].value);
                q.push(e[p].to);
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
    tail=1;//边表的尾后索引
    ans=0;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>v>>w>>c;
        original[i].from=v;
        original[i].to=w;
        original[i].value=c;
        add_edge(v,w,c);
        add_edge(w,v,c);
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=inf;//顺便把dist初始化了
    }
    Dijkstra(1);
    //清除原图
    for(int i=1;i<=n;i++)
        head[i]=0;
    tail=2;//重置边表索引，从2开始，一对一对的重建
    /*每一条在最短路上的原始边，从镜像点连到入点，再连一条反向边，但1和n不拆，需要特判*/
    for(int i=0;i<m;i++){
        if(dist[original[i].from]+original[i].value==dist[original[i].to]){
            if(original[i].from==1){
                add_edge(original[i].from,original[i].to,inf);
                add_edge(original[i].to,original[i].from,0);
            }else{
                add_edge(original[i].from+n,original[i].to,inf);
                add_edge(original[i].to,original[i].from+n,0);
            }
        }
        if(dist[original[i].to]+original[i].value==dist[original[i].from]){
            if(original[i].to==1){
                add_edge(original[i].to,original[i].from,inf);
                add_edge(original[i].from,original[i].to,0);
            }else{
                add_edge(original[i].to+n,original[i].from,inf);
                add_edge(original[i].from,original[i].to+n,0);
            }
        }
    }
    /*把顶点及其镜像连起来*/
    for(int i=2;i<n;i++){
        add_edge(i,i+n,vomit[i]);
        add_edge(i+n,i,0);
    }
    while(maxflow(1,n));
    cout<<ans<<endl;
    /*
    for(int i=2;i<tail;i++){
        cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].value<<endl;
    }
    cout<<endl;
    */
}