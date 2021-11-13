/*洛谷 P3376 【模板】网络最大流
 *输入格式
 *第一行包含四个正整数n,m,s,t，分别表示点的个数、有向边的个数、源点序号、汇点序号。
 *接下来m行每行包含三个正整数u_i,v_i,w_i，表示第i条有向边从u_i出发，到达v_i
 *边权为w_i（即该边最大流量为w_i）。
 *输出格式
 *一行，包含一个正整数，即为该网络的最大流。
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
class flowedge{
    int m_v;
    int m_w;
    int m_capacity;
    int m_flow=0;
    public:
    void set(int v,int w,int capacity){
        m_v=v;
        m_w=w;
        m_capacity=capacity;
    }
    int from(){return m_v;}
    int to(){return m_w;}
    int other(int vertex){
        if(vertex==m_v)
            return m_w;
        else if(vertex==m_w)
            return m_v;
        else
            throw "vertex is error!";
    }
    int flow(){return m_flow;}
    int residualCapacityTo(int vertex){
        if(vertex==m_v)
            return m_flow;
        else if(vertex==m_w)
            return m_capacity-m_flow;
        else
            throw "vertex is error!";
    }
    void addResidualFlowTo(int vertex,int delta){
        if(vertex==m_v)
            m_flow-=delta;
        else if(vertex==m_w)
            m_flow+=delta;
        else
            throw "vertex is error!";
    } 
};
class flowgraph{
    int m_v;
    int m_e;
    int m_tail=0;
    flowedge *m_allEdge;
    vector<flowedge *> *m_adj;
    public:
    flowgraph(int v,int e){
        m_adj=new vector<flowedge *>[v+1];
        m_allEdge=new flowedge[e];
    }
    ~flowgraph(){
        delete[] m_adj;
        delete[] m_allEdge;
    }
    void add_edge(int start,int target,int value){
        m_allEdge[m_tail].set(start,target,value);
        m_adj[start].push_back(m_allEdge+m_tail);
        m_adj[target].push_back(m_allEdge+m_tail);
        m_tail++;
    }
    vector<flowedge *> &adj(int vertex){
        return *(m_adj+vertex);
    }
};
const int N=200,M=5000;
bool marked[N+1];
int cf[N+1];
flowedge* edgeTo[N+1];
unsigned long long maxflow=0;
bool hasAugmentingPath(flowgraph &g,int s,int t){
    queue<int> q;
    q.push(s);
    memset(marked,0,sizeof(marked));
    marked[s]=true;
    cf[s]=__INT_MAX__;
    while(!q.empty()&&!marked[t]){
        int current=q.front();
        q.pop();
        for(auto v:g.adj(current)){
            int w=v->other(current);
            if(!marked[w]&&v->residualCapacityTo(w)){
                q.push(w);
                edgeTo[w]=v;
                marked[w]=true;
                cf[w]=min(cf[current],v->residualCapacityTo(w));
            }
        }
    }
    return marked[t];
}
void FordFulkerson(flowgraph &g,int s,int t){
    while(hasAugmentingPath(g,s,t)){
        for(int v=t;v!=s;v=edgeTo[v]->other(v)){
            edgeTo[v]->addResidualFlowTo(v,cf[t]);
        }
        maxflow+=cf[t];
    }
}
int main(){
    int n,m,s,t,u,v,w;
    cin>>n>>m>>s>>t;
    flowgraph g(n,m);
    for (int i=0;i<m;i++){
        cin>>u>>v>>w;
        g.add_edge(u,v,w);
    }
    FordFulkerson(g,s,t);
    cout<<maxflow<<endl;
}