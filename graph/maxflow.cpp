/*洛谷 P3376 【模板】网络最大流
 *输入格式
 *第一行包含四个正整数n,m,s,t，分别表示点的个数、有向边的个数、源点序号、汇点序号。
 *接下来m行每行包含三个正整数u_i,v_i,w_i，表示第i条有向边从u_i出发，到达v_i
 *边权为w_i（即该边最大流量为w_i）。
 *输出格式
 *一行，包含一个正整数，即为该网络的最大流。
*/

#include <iostream>
#include <cstring>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <limits>

using namespace std;
const int N=200,M=5000;
struct edge{
    int from;//剩余网络需要逆向边
    int to;
    int next=0;
    unsigned int capacity;
    unsigned int flow = 0; //流
}edges[M+1];
int adj[N+1];//邻接边，每个顶点的第一条边的编号；
/*
void update(int s, int t, unsigned int cf)
{
    int current = t;
    while (current != s)
    {
        if (path[current]->original)
        {
            path[current]->capacity -= cf;
            path[current]->flow += cf;
            path[current]->rev->capacity = path[current]->flow;
            path[current]->rev->flow = 0;
        }
        else
        {
            path[current]->rev->capacity += cf;
            path[current]->rev->flow -= cf;
            path[current]->capacity = path[current]->rev->flow;
            path[current]->flow = 0;
        }
        current = path[current]->from;
    }
}
unsigned int bfs(int s, int t)
{
    unsigned int cf = 1 << 31; //残余流量
    queue<int> q;
    int marked[N + 1];
    memset(path, 0, sizeof(list<edge>::iterator) * (N + 1));
    memset(marked, 0, sizeof(int) * (N + 1));
    marked[s] = 1;
    q.push(s);
    if (s == t)
        return 0;
    while (!q.empty() && marked[t] == 0)
    {
        int current = q.front();
        q.pop();
        for (auto p = graph[current].begin(); p != graph[current].end(); p++)
        {
            if (marked[p->to] == 0 && p->capacity > 0)
            {
                marked[p->to] = 1;
                path[p->to] = p;
                q.push(p->to);
                if (cf > p->capacity)
                    cf = p->capacity;
            }
        }
    }
    if (marked[t] == 1)
    {
        update(s, t, cf);
        return cf;
    }
    else
        return 0;
}
*/
int main(){
    int n,m,s,t,u,v,w;
    unsigned long long maxflow = 0;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1;i<=m;i++){
        cin >> u >> v >> w;
        scanf("%d%d%d",&u,&v,&w);
        edges[i].from=u;
        edges[i].to=v;
        edges[i].capacity=w;
        edges[i].next=adj[u];
        adj[u]=i;
    }
}
    /*
    while (bfs(s, t))
        ;
    for (auto p = graph[s].begin(); p != graph[s].end(); p++)
    {
        maxflow += p->flow;
    }
    cout << maxflow << endl;
    */
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