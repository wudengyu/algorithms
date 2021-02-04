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
    bool operator==(const egde &a) const{
        return from==a.from&&to==a.to;
    }
};
struct vertex{
    int vomit;
    long long dist;
    forward_list<egde> adjoin;
}graph[N];
int mask[N];
struct comp{
    bool operator()(egde a,egde b){
        return graph[a.to].dist>graph[b.to].dist;
    }
};
/*
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
*/
void Dijkstra(int begin){
    priority_queue<egde,vector<egde>,comp> pq;
    graph[begin].dist=0;
    mask[begin]=1;
    for(auto p=graph[begin].adjoin.begin();p!=graph[begin].adjoin.end();p++){
        pq.push(*p);
    }
    while(!pq.empty()){
        egde current=pq.top();
        pq.pop();
        if(mask[current.to]){
            graph[current.from].adjoin.remove(current);
            continue;
        }
        mask[current.to]=1;
        for(auto e=graph[current.to].adjoin.begin();e!=graph[current.to].adjoin.end();e++){
            if(graph[e->from].dist+e->cost<graph[e->to].dist){
                graph[e->to].dist=graph[e->from].dist+e->cost;
                pq.push(*e);
            }
        }
    }
}

int main(){
    int n,m;
    int a,b,d;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a].adjoin.push_front({a,b,d});
        graph[b].adjoin.push_front({b,a,d});
    }
    for(int i=1;i<=n;i++){
        cin>>graph[i].vomit;
        graph[i].dist=__LONG_LONG_MAX__;//顺便把dist初始化了
        mask[i]=0;
    }
    Dijkstra(1);
    for(int i=1;i<=n;i++){
        cout<<"V("<<i<<"):";
        for(auto e=graph[i].adjoin.begin();e!=graph[i].adjoin.end();e++){
            cout<<e->to<<" ";
        }
        cout<<endl;
    }
}