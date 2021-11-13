#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
class flowedge{
    int m_v;
    int m_w;
    int m_cost;
    int m_capacity;
    int m_flow=0;
    public:
    void set(int v,int w,int capacity,int cost=0){
        m_v=v;
        m_w=w;
        m_capacity=capacity;
        m_cost=cost;
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
    int costTo(int vertex){
        if(vertex==m_v)
            return -m_cost;
        else if(vertex==m_w)
            return m_cost;
        else
            throw "vertex is error!";
    }
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
    void add_edge(int start,int target,int value,int cost){
        m_allEdge[m_tail].set(start,target,value,cost);
        m_adj[start].push_back(m_allEdge+m_tail);
        m_adj[target].push_back(m_allEdge+m_tail);
        m_tail++;
    }
    vector<flowedge *> &adj(int vertex){
        return *(m_adj+vertex);
    }
};
const int N=100;
bool marked[2*(N+1)];
int dist[2*(N+1)];
flowedge* edgeTo[2*(N+1)]={};
int mincost=0,maxflow=0;
bool hasAugmentingPath(flowgraph &g,int s,int t){
    queue<int> q;
    q.push(s);
    memset(marked,0,sizeof(marked));
    memset(edgeTo,0,sizeof(edgeTo));
    memset(dist,0x3f,sizeof(dist));
    marked[s]=true;
    dist[s]=0;
    while(!q.empty()){
        int current=q.front();
        q.pop();
        marked[current]=false;
        for(auto v:g.adj(current)){
            int w=v->other(current);
            if(dist[w]>dist[current]+v->costTo(w)&&v->residualCapacityTo(w)){
                dist[w]=dist[current]+v->costTo(w);
                edgeTo[w]=v;
                if(!marked[w]){
                    q.push(w);
                    marked[w]=true;
                }
            }
        }
    }
    return edgeTo[t]!=NULL;
}
void FordFulkerson(flowgraph &g,int s,int t){
    while(hasAugmentingPath(g,s,t)){
        int delta=__INT_MAX__;
        for(int v=t;v!=s;v=edgeTo[v]->other(v)){
            if(edgeTo[v]->residualCapacityTo(v)<delta)
                delta=edgeTo[v]->residualCapacityTo(v);
        }
        for(int v=t;v!=s;v=edgeTo[v]->other(v)){
            edgeTo[v]->addResidualFlowTo(v,delta);
        }
        mincost+=delta*dist[t];
        maxflow+=delta;

    }
}

int main() {
    int n,s[N+1],average;
    long long sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        sum+=s[i];
    }
    average=sum/n;
    flowgraph g(n+1,4*n);
    for(int i=1;i<=n;i++){
        int previous=i-1;
        int next=i+1;
        if(previous==0)
            previous+=n;
        if(next>n)
            next-=n;
        if(s[i]>average)
            g.add_edge(0,i,s[i]-average,0);
        g.add_edge(i,previous,__INT_MAX__,1);
        g.add_edge(i,next,__INT_MAX__,1);
        if(s[i]<average)
            g.add_edge(i,n+1,average-s[i],0);
    }
    FordFulkerson(g,0,n+1);
    cout<<mincost<<endl;
    for(int i=1;i<=n;i++){
        for(auto v:g.adj(i)){
            if(v->to()==v->other(i)&&v->to()!=n+1)
            cout<<i<<"->"<<v->other(i)<<":"<<v->flow()<<endl;
        }
    }
}
