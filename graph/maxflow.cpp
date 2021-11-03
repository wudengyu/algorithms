/*洛谷 P3376 【模板】网络最大流
 *输入格式
 *第一行包含四个正整数n,m,s,t，分别表示点的个数、有向边的个数、源点序号、汇点序号。
 *接下来m行每行包含三个正整数u_i,v_i,w_i，表示第i条有向边从u_i出发，到达v_i
 *边权为w_i（即该边最大流量为w_i）。
 *输出格式
 *一行，包含一个正整数，即为该网络的最大流。
*/

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N=200,M=5000;
struct{
    int to;
    int next=0;
    unsigned int capacity;//残余流量
}e[2*(M+1)];//从2开始，偶数保存正向边，奇数保存反向边，这样就可以用xor 1快速找到反向边
int head[N+1];//每个顶点的第一条边的编号
int path[N+1];//到达顶点的边
//int marked[N+1];
void update(int s,int t,unsigned int cf){
    int current = t;
    while (current!=s){
        int p=path[current];
        e[p].capacity-=cf;
        e[p^1].capacity+=cf;
        current=e[p^1].to;
    }
}
int bfs(int s, int t){
    unsigned int cf[N+1]; //当前寻路过程中，到达顶点的最小残余流量
    queue<int> q;
    //memset(marked,0,(N+1)*sizeof(int));
    int marked[N+1]={};
    marked[s]=1;
    cf[s]=2147483648;
    q.push(s);
    if (s==t)
        return 0;
    while (!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
        for (int p=head[current];p!=0;p=e[p].next){
            if (marked[e[p].to]==0&&e[p].capacity>0){
                marked[e[p].to]=1;
                path[e[p].to]=p;
                cf[e[p].to]=min(cf[current],e[p].capacity);
                q.push(e[p].to);
            }
        }
    }
    if(marked[t]==1){
        update(s,t,cf[t]);
        return 1;
    }else
        return 0;
}
int main(){
    int n,m,s,t,u,v,w;
    unsigned long long maxflow=0;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=2;i<=2*m;i+=2){
        scanf("%d%d%d",&u,&v,&w);
        e[i].to=v;
        e[i].capacity=w;
        e[i].next=head[u];
        head[u]=i;
        e[i^1].to=u;
        e[i^1].capacity=0;
        e[i^1].next=head[v];
        head[v]=i^1;
    }
    while(bfs(s,t)!=0);
    for(int p=head[t];p!=0;p=e[p].next){
        if(p%2==1)
            maxflow+=e[p].capacity;
    }
    cout << maxflow << endl;
}