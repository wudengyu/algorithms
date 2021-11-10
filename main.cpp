#include <iostream>
#include <vector>
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
        m_adj=new vector<flowedge *>[v];
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
    void adj(int vertex){
        for(auto v:m_adj[vertex]){
            cout<<v->from()<<"->"<<v->to()<<" "<<v->residualCapacityTo(vertex)<<endl;
        }
    }
};
int main() {
    flowgraph g(4,4);
    g.add_edge(0,1,1);
    g.add_edge(0,2,2);
    g.add_edge(1,2,3);
    g.add_edge(2,3,4);
    g.adj(2);
}
