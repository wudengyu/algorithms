/*洛谷 P3381 【模板】最小费用最大流
 *求网络流量最大的情况下最小费用
 *解题思路：
 *直觉是找一条最短路，然后跑满，再继续找……，但是这样得到的总流量并不一定是最大流，
 *找最大流的过程是要允许反向流量的，也就是允许流回去重新找别的路径，显然，回流的花费就应该是负值，
 *那么Dijkstra算法就不行了，它是基于访问过的点的距离不会再变化（变大一定不是最短路，所以忽略），
 *如果有负向边，那距离可能会变小，变小以后又要重新算，无穷无尽了，
 *所以对于有负向边的图，要用Bellman-Ford算法，区别就是用队列代替优先队列，还要保证不重复入队，
 *采用优先队列重复入队无所谓，因为后面入队的一定距离更短，一定先出队，后面出队的就变成了失效边，不影响结果，
 *而采用先进先出队列，重复入队会使得同一条边松驰多次，关键是因为有负向边存在，多余的松驰操作会使距离越来越小
 *此题的坑是有的测试数据汇点会有出边，有点测试数据cost又会有0，计算最大流时，用汇点的反向边（流出）加总时不能加原始的流出的边，所以要
 *用cost流出为负来判断，但最后一个测试点汇点的cost恰好为0，就判断不了，最后加=0过。
 *但是如果汇点又有cost为0的原始出边，那就不行，从源点的流出来统计恐怕也不行。
 *如果那样，可能只有老老实实的把容量和流分开记录，而不能偷懒只用残余流量来计算了。
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N=5000,M=50000;
struct edge{
    int from;
    int to;
    int flow;
    int cost;
    int next=0;//下一条边
}e[2*M+3];
int tail;//边表的尾后索引
int head[N+1];
long long mincost,maxflow;
void add_edge(int from,int to,int flow,int cost){
    e[tail].from=from;
    e[tail].to=to;
    e[tail].flow=flow;
    e[tail].cost=cost;
    e[tail].next=head[from];
    head[from]=tail;
    tail++;
}
void update(int s,int t,int path[],int cf){
    int current=t;
    while(current!=s){
        e[path[current]].flow-=cf;
        e[path[current]^1].flow+=cf;
        mincost+=cf*e[path[current]].cost;
        current=e[path[current]].from;
    }
}
int BellmanFord(int start,int termanil){
    int cf[N+1]={}; //当前寻路过程中，到达顶点的最小残余流量
    int edgeTo[N+1]={};//到达节点的边的索引
    long long distTo[N+1]={};
    memset(distTo,0x7f,sizeof distTo);
    bool onQ[N+1]={};
    queue<int> q;
    q.push(start);
    onQ[start]=true;
    distTo[start]=0;
    cf[start]=__INT_MAX__;
    /*似乎不可能有这种情况*/
    if(start==termanil)
        return 0;
    while(!q.empty()){
        int current=q.front();
        q.pop();
        onQ[current]=false;
        for(int p=head[current];p!=0;p=e[p].next){
            if(e[p].flow>0&&distTo[current]+e[p].cost<distTo[e[p].to]){
                distTo[e[p].to]=distTo[current]+e[p].cost;
                edgeTo[e[p].to]=p;
                cf[e[p].to]=min(cf[current],e[p].flow);
                if(!onQ[e[p].to]){
                    q.push(e[p].to);
                    onQ[e[p].to]=true;
                }
            }
        }
    }
    if(edgeTo[termanil]){
        update(start,termanil,edgeTo,cf[termanil]);
        return 1;
    }else
        return 0;
}
int main(){
    int n,m,s,t,u,v,w,c;
    mincost=0;
    maxflow=0;
    tail=2;
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w>>c;
        add_edge(u,v,w,c);
        add_edge(v,u,0,-c);//反向边的残余流量为0，费用是相反数
    }
    while(BellmanFord(s,t));

    cout<<endl;
    for(int i=2;i<2*m+2;i++)
        cout<<e[i].from<<" "<<e[i].to<<" "<<e[i].flow<<" "<<e[i].cost<<endl;

    for(int p=head[t];p!=0;p=e[p].next){
        if(e[p].cost<=0)
            maxflow+=e[p].flow;
    }
    cout<<maxflow<<" "<<mincost<<endl;
}