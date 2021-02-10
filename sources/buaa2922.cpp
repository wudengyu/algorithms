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
const int N=500;
struct egde{
    int from;
    int to;
    int cost;
    int capacity=1e9;//容量
    int flow=0;//流
    bool original=true;
    list<egde>::iterator rev;
    egde(){};
    egde(int f,int t,int c){
        from=f;
        to=t;
        cost=c;
    }
    egde(int f,int t,bool o){
        from=f;
        to=t;
        cost=0;
        capacity=0;
        original=o;
    }
    egde(int f,int t,int c,int ca){
        new(this) egde(f,t,c);
        capacity=ca;
    }
};
struct vertex{
    int e=0;//excess flow
    int h=0;
    list<egde> adjoin;
}graph[2*N+1];
list<egde>::iterator path[2*N+1];
int vomit[N+1];
int marked[2*N+1];
long long dist[N+1];
struct comp{
    bool operator()(list<egde>::iterator a,list<egde>::iterator b){
        return dist[a->to]>dist[b->to];
    }
};
void Dijkstra(int begin){
    priority_queue<list<egde>::iterator,vector<list<egde>::iterator>,comp> pq;
    dist[begin]=0;
    for(auto p=graph[begin].adjoin.begin();p!=graph[begin].adjoin.end();p++){
        dist[p->to]=p->cost;
        pq.push(p);
    }
    while(!pq.empty()){
        list<egde>::iterator current=pq.top();
        pq.pop();
        if(dist[current->from]+current->cost>dist[current->to]){
            current->capacity=0;
            current->original=false;
        }else{
            for(auto p=graph[current->to].adjoin.begin();p!=graph[current->to].adjoin.end();p++){
                if(dist[p->from]+p->cost<dist[p->to]){
                    dist[p->to]=dist[p->from]+p->cost;
                }
                pq.push(p);
            }
        }
    }
}
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
int main(){
    int n,m;
    int a,b,d;
    unsigned long long maxflow=0;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a].adjoin.push_front(egde(a,b,d));
        graph[b].adjoin.push_front(egde(b,a,d));
        graph[a].adjoin.begin()->rev=graph[b].adjoin.begin();
        graph[b].adjoin.begin()->rev=graph[a].adjoin.begin();
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=__LONG_LONG_MAX__;//顺便把dist初始化了
    }
    Dijkstra(1);
    splitvertex(1,n,n);
    while(bfs(1,n));
    for(auto p=graph[1].adjoin.begin();p!=graph[1].adjoin.end();p++){
        maxflow+=p->flow;
    }
    cout<<maxflow<<endl;
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