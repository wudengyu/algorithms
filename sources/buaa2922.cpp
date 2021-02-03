#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<forward_list>
#include<limits>
using namespace std;
const int N=501;
struct egde{
    int from;
    int to;
    int cost;
};
unsigned long long dist[N];
struct comp{
    bool operator()(int a,int b){
        return dist[a]>dist[b];
    }
};
int vomit[N],path[N];
vector<forward_list<egde>> graph(N);
vector<set<int>> preorder(N);
int traversal(int begin,int end,int step,int vertex){
    if(vertex==begin){
        int min_vomit=1e9;
        for(int i=1;i<=step-1;i++){
            //cout<<path[i]<<" ";
            if(vomit[path[i]]<min_vomit)
                min_vomit=vomit[path[i]];
        }
        //cout<<"min_vomit="<<min_vomit<<endl;
        for(int i=1;i<step-1;i++){
            vomit[path[i]]-=min_vomit;
        }
        return min_vomit;
    }else{
        path[step]=vertex;
        int returnvalue=0;
        for(auto i=preorder[vertex].begin();i!=preorder[vertex].end();i++){
            returnvalue+=traversal(begin,end,step+1,*i);
        }
        return returnvalue;
    }
}
void Dijkstra(int begin){
    priority_queue<int,vector<int>,comp> pq;
    set<int> visited;
    dist[begin]=0;
    pq.push(begin);
    while(!pq.empty()){
        int current;
        do{
            current=pq.top();
            pq.pop();
        }while(visited.find(current)!=visited.end()&&!pq.empty());
        if(visited.find(current)!=visited.end()) break;
        visited.insert(current);
        for(auto e=graph[current].begin();e!=graph[current].end();e++){
            if(dist[e->from]+e->cost<dist[e->to]){
                dist[e->to]=dist[e->from]+e->cost;
                preorder[e->to].clear();
                preorder[e->to].insert(e->from);
                pq.push(e->to);
            }else if(dist[e->from]+e->cost==dist[e->to]){
                preorder[e->to].insert(e->from);
                pq.push(e->to);
            }
        }
    }
    cout<<traversal(1,7,0,7)<<endl;
}

int main(){
    int n,m;
    int a,b,d;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a].push_front({a,b,d});
        graph[b].push_front({b,a,d});
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=UINT64_MAX;//顺便把dist初始化了
    }
    Dijkstra(1);
}