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
int vomit[N];
vector<forward_list<egde>> graph(N);
vector<set<int>> preorder(N);
void Dijkstra(int begin){
    queue<egde> q;//因为要找出所有最短路径，而不是找到一条就停止，所以就不必采用优先队列
    dist[begin]=0;
    int current=begin;
    do{
        for(auto e=graph[current].begin();e!=graph[current].end();e++){
            if(dist[e->from]+e->cost<dist[e->to]){
                dist[e->to]=dist[e->from]+e->cost;
                preorder[e->to].clear();
                preorder[e->to].insert(e->from);
                q.push(*e);
            }else if(dist[e->from]+e->cost==dist[e->to]){
                preorder[e->to].insert(e->from);
                q.push(*e);
            }
        }
        current=q.front().to;
        q.pop();
    }while(!q.empty());
    for(auto a=preorder[4].begin();a!=preorder[4].end();a++){
        cout<<*a<<" ";
    }
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