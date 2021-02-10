#include<iostream>
#include<cstring>
#include<list>
#include<stack>
#include<queue>
#include<set>
#include<limits>

using namespace std;
const int N=200;
struct edge{
    int from;
    int to;
    unsigned int capacity;
    unsigned int flow=0;//流
    bool original=true;
    list<edge>::iterator rev;
    edge(){};
    edge(int x,int y,int z=0){
        from=x;
        to=y;
        capacity=z;
    }
    edge(int x ,int y,bool o){
        from=x;
        to=y;
        capacity=0;
        original=o;
    }
};
list<edge> graph[N+1];
list<edge>::iterator path[N+1];
void update(int s,int t,unsigned int cf){
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
unsigned int bfs(int s,int t){
    unsigned int cf=1<<31;//残余流量
    queue<int> q;
    int marked[N+1];
    memset(path,0,sizeof(list<edge>::iterator)*(N+1));
    memset(marked,0,sizeof(int)*(N+1));
    marked[s]=1;
    q.push(s);
    if(s==t)
        return 0;
    while(!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
        for(auto p=graph[current].begin();p!=graph[current].end();p++){
            if(marked[p->to]==0&&p->capacity>0){
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
int main(){
    int n,m,s,t,u,v,w;
    unsigned long long maxflow=0;
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        graph[u].push_front(edge(u,v,w));
        graph[v].push_front(edge(v,u,false));
        graph[u].begin()->rev=graph[v].begin();
        graph[v].begin()->rev=graph[u].begin();
    }
    while(bfs(s,t));
    for(auto p=graph[s].begin();p!=graph[s].end();p++){
        maxflow+=p->flow;
    }
    cout<<maxflow<<endl;
    /*
    for(int i=1;i<=n;i++){
        if(!graph[i].empty()){
            for(auto p=graph[i].begin();p!=graph[i].end();p++){
                cout<<"("<<p->from<<","<<p->to<<")=["<<p->capacity<<","<<p->flow<<"] ";
                cout<<"|"<<p->rev->from<<","<<p->rev->to<<"| ";
            }
            cout<<endl;
        }
    }
    */
    
}