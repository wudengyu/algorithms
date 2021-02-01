#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<forward_list>
using namespace std;
int vomit[501];
struct egde{
    int from;
    int to;
    int cost;
    bool operator<(const egde &a) const{
        return cost>a.cost;
    } 
};
void Dijkstra(vector<forward_list<egde>> graph,int begin,int end){
    priority_queue<egde> pq;
    map<int,int> from={{begin,0}};
    for(auto e=graph[begin].begin();e!=graph[begin].end();e++){
            pq.push(*e);
    }
    while(from.find(end)==from.end()&&!pq.empty()){
        int vertex=pq.top().to;
        if(from.find(vertex)==from.end()){
            from[vertex]=pq.top().from;
            for(auto e=graph[vertex].begin();e!=graph[vertex].end();e++){
                pq.push(*e);
            }
        }
        pq.pop();
    }
    int v=from[end];
    int min=1e9;
    while(v!=1){
        if(min>vomit[v])
            min=vomit[v];
        v=from[v];
    }
    cout<<min<<endl;
}

int main(){
    int n,m;
    int a,b,d;
    cin>>n>>m;
    vector<forward_list<egde>> graph(n+1);
    
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a].push_front({a,b,d});
        graph[b].push_front({b,a,d});
    }
    for(int i=1;i<=n;i++)
        cin>>vomit[i];
    Dijkstra(graph,1,n);
}