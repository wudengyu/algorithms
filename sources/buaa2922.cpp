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
    int f=0;//流
    bool original=true;
};
struct vertex{
    int e=0;//excess flow
    int h=0;
    list<egde> adjoin;
}graph[2*N+1];
int vomit[N+1];
int visited[2*N+1],mask[2*N+1];
long long dist[N+1];
struct comp{
    bool operator()(list<egde>::iterator a,list<egde>::iterator b){
        return dist[a->to]>dist[b->to];
    }
};
egde& search(int u,int v){
    bool found=false;
    for(auto p=graph[u].adjoin.begin();p!=graph[u].adjoin.end();p++){
        
    }
}
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
            graph[current->to].adjoin.erase(current);
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
            graph[length+i-1].adjoin.swap(graph[i].adjoin);
            for(auto p=graph[length+i-1].adjoin.begin();p!=graph[length+i-1].adjoin.end();p++){
                p->from=length+i-1;
            }
            graph[i].adjoin.push_front({from:i,to:length+i-1,cost:0,capacity:vomit[i]});
        }
    }

}
int dfs(int s,int t,int length){
    queue<list<egde>::iterator> q;
    stack<list<egde>::iterator> temppath;
    int cf=0;//残存容量
    //memset(mask,0,sizeof(int)*(2*N+1));
    for(auto p=graph[s].adjoin.begin();p!=graph[s].adjoin.end();p++){
        if(p->capacity-p->f>0){
            q.push(p);
            temppath.push(p);
            if(p->to==t)
                break;
        }
    }
    while(!q.empty()&&q.back()->to!=t){
        list<egde>::iterator current=q.front();
        q.pop();
        for(auto p=graph[current->to].adjoin.begin();p!=graph[current->to].adjoin.end();p++){
            if(p->capacity-p->f>0){
                q.push(p);
                temppath.push(p);
                if(p->to==t)
                    break;
            }
        }
    }//循环结束时，要么队列为空（没找到路径），要么队尾是到目标的一条边
    if(!q.empty()){
        while(q.front()->to!=t)
            q.pop();
        cf=q.back()->capacity-q.back()->f;
        while(q.back()->from!=s){
            while(temppath.top()->to!=q.back()->from)
                temppath.pop();
            q.push(temppath.top());
            if(cf>q.back()->capacity-q.back()->f)
                cf=q.back()->capacity-q.back()->f;
        }
    }//从栈中取得增广路径并计算残存容量；
    /*
    while(!q.empty()){
        list<egde>::iterator current=q.front();
        q.pop();
    }*/
    while(!q.empty()){
        cout<<"("<<q.front()->from<<","<<q.front()->to<<")";
        q.pop();
    }
    cout<<cf;
    return 0;
}
int main(){
    int n,m;
    int a,b,d;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a].adjoin.push_front({from:a,to:b,cost:d});
        graph[b].adjoin.push_front({from:b,to:a,cost:d});
    }
    for(int i=1;i<=n;i++){
        cin>>vomit[i];
        dist[i]=__LONG_LONG_MAX__;//顺便把dist初始化了
    }
    Dijkstra(1);
    splitvertex(1,n,n);
    dfs(1,n,n);
    /*
    for(int i=1;i<2*N+1;i++){
        if(!graph[i].adjoin.empty()){
            for(auto e=graph[i].adjoin.begin();e!=graph[i].adjoin.end();e++){
                cout<<"("<<e->from<<","<<e->to<<")={"<<e->capacity<<","<<e->f<<"} ";
            }
            cout<<endl;
        }
    }
    */
}