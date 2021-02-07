#include<iostream>
#include<vector>
#include<queue>
#include<map>
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
    int c=1e9;//容量
    int f=0;//流
    list<egde>::iterator rev;//反向边
};
struct vertex{
    int e=0;//excess flow
    int h=0;
    list<egde> adjoin;
}graph[2*N+1];
int vomit[N+1];
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
            graph[current->from].adjoin.erase(current);
            graph[current->to].adjoin.erase(current->rev);//反向边也删除
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
void push(list<egde>::iterator side){
    int delta=min(graph[side->from].e,side->c);
    side->f+=delta;
    graph[side->from].e-=delta;
    graph[side->to].e+=delta;
    
}
void generic_push_relabel(int s,int t,int length){
    /*除了起点和终点，其余每个点都拆成两个点；*/
    for(int i=2;i<length;i++){
        graph[i].adjoin.push_front({i,N+i,0,vomit[i],0});
        graph[N+i].adjoin.push_front({N+i,i,0,vomit[i],0});
        graph[i].adjoin.front().rev=graph[N+i].adjoin.begin();
        graph[N+i].adjoin.front().rev=graph[i].adjoin.begin();
    }
    graph[s].h=2*length-2;
    for(auto p=graph[s].adjoin.begin();p!=graph[s].adjoin.end();p++){
        p->f=p->c;
        graph[p->to].e=p->c;
        graph[s].e-=p->c;
        graph[p->to].adjoin.push_front({p->to,p->from,p->cost,p->c,0,p});
        p->rev=graph[p->to].adjoin.begin();
    }
    bool exists=true;
    while(exists){
        exists=false;
        for(int i=1;i<=length;i++){
            if(graph[i].e>0){
                for(auto p=graph[i].adjoin.begin();p!=graph[i].adjoin.end();p++){
                    if(p->c>0&&graph[i].h==graph[p->from].h+1)
                }
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
        graph[a].adjoin.front().rev=graph[b].adjoin.begin();
        graph[b].adjoin.front().rev=graph[a].adjoin.begin();
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=__LONG_LONG_MAX__;//顺便把dist初始化了
    }
    Dijkstra(1);
    generic_push_relabel(1,n,n);
    for(int i=1;i<2*N+1;i++){
        if(!graph[i].adjoin.empty()){
            for(auto e=graph[i].adjoin.begin();e!=graph[i].adjoin.end();e++){
                cout<<"("<<e->from<<","<<e->to<<")={"<<e->c<<","<<e->f<<"} ";
            }
            cout<<endl;
        }
    }
    cout<<graph[1].e<<" "<<graph[1].h<<endl;
}