#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<list>
#include<forward_list>
#include<limits>
using namespace std;
const int N=501;
struct egde{
    int from;
    int to;
    int cost;
};
struct vertex{
    int vomit;
    long long dist;
    list<egde> adjoin;
}graph[N];
struct comp{
    bool operator()(list<egde>::iterator a,list<egde>::iterator b){
        return graph[a->to].dist>graph[b->to].dist;
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
    priority_queue<list<egde>::iterator,vector<list<egde>::iterator>,comp> pq;
    graph[begin].dist=0;
    for(auto p=graph[begin].adjoin.begin();p!=graph[begin].adjoin.end();p++){
        graph[p->to].dist=p->cost;
        pq.push(p);
    }
    while(!pq.empty()){
        list<egde>::iterator current=pq.top();
        pq.pop();
        if(graph[current->from].dist+current->cost>graph[current->to].dist){
            graph[current->from].adjoin.erase(current);
        }else{
            for(auto p=graph[current->to].adjoin.begin();p!=graph[current->to].adjoin.end();p++){
                if(graph[p->from].dist+p->cost<graph[p->to].dist){
                    graph[p->to].dist=graph[p->from].dist+p->cost;
                }
                pq.push(p);
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