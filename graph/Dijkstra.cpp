#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
struct edge{
    int to;
    unsigned int cost;
};
class graph{
    int m_vnum;
    int m_enum;
    int m_tail=0;
    edge *m_allEdge;
    vector<edge *> *m_adj;
    public:
    graph(int v,int e){
        m_vnum=v;
        m_enum=e;
        m_adj=new vector<edge *>[v+1];
        m_allEdge=new edge[e];
    }
    ~graph(){
        delete[] m_adj;
        delete[] m_allEdge;
    }
    int v(){return m_vnum;}
    void add_edge(int start,int target,unsigned int value){
        m_allEdge[m_tail].to=target;
        m_allEdge[m_tail].cost=value;
        m_adj[start].push_back(m_allEdge+m_tail);
        m_tail++;
    }
    vector<edge *> &adj(int vertex){
        return *(m_adj+vertex);
    }
};
const int N=100000,M=200000;
const unsigned int inf=(unsigned int)(1<<31)-1;
bool marked[N+1];
unsigned int dist[N+1];
stack<int> st;
struct comp{
    bool operator()(const int a,const int b){
        return dist[a]>dist[b];
    }
};
void dfs(graph& g,int s){
    stack<int> r;
    memset(marked,0,sizeof(marked));
    r.push(s);
    while(!r.empty()){
        int current=r.top();
        r.pop();
        marked[current]=true;
        cout<<current<<" ";
        for(auto p:g.adj(current)){
            if(!marked[p->to]){
                r.push(p->to);
            }
        }
    }
}
void Dijkstra(graph &g,int s){
    priority_queue<int,vector<int>,comp> q;
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        int current=q.top();
        q.pop();
        for(auto p:g.adj(current)){
            if(dist[p->to]>dist[current]+p->cost){
                dist[p->to]=dist[current]+p->cost;
                q.push(p->to);
            }
        }
    }
}
void dag(graph &g,int s){
    dfs(g,s);
    dist[s]=0;
    while(!st.empty()){
        int v=st.top();
        st.pop();
        for(auto e:g.adj(v)){
            if(dist[e->to]>dist[v]+e->cost)
                dist[e->to]=dist[v]+e->cost;
        }
    }
}
int main(){
    int n,m,s,u,v,w;
    scanf("%d%d%d",&n,&m,&s);
    graph g(n,m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        g.add_edge(u,v,w);
    }
    for(int i=1;i<=n;i++){
        dist[i]=inf;
    }
    //Dijkstra(g,s);
    dfs(g,s);
    /*
    for(int i=1;i<=n;i++)
        cout<<dist[i]<<" ";
    cout<<endl;
    */
}