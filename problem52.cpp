/*零崎的补番计划Ⅲ
 *最短路径问题，Dijkstra算法，
 *图用邻接矩阵表示。一个集合s放最短路径上的点，一个数组dist放从起点到各点的最短路径的距离；
 *这题实际上应该用Floyed算法，也就是重复执行Dijkstra算法n次，把每对顶点之间的最短路径都算出来
 *然后再执行查询。Floyed算法其实代码还要短一些，但是要难理解一点，因为要理解找最短路径中间点的
 *次序无关紧要，因此Floyed算法才不需要像Dijkstra算法那样要按顺序找最短距离。
*/
#include <iostream>
#define N 500
using namespace std;
void shortpath(int graph[N][N],int n,int v,int dist[N]){
    int s[N],u;
    unsigned max;
    for(int i=0;i<n;i++){
        s[i]=0;
        dist[i]=graph[v][i];
    }
    s[v]=1;//将节点v加入集合；
    for(int num=1;num<n;num++){
        max=-1;
        u=v;
        for(int i=0;i<n;i++){
            if(s[i]==0){
                if(dist[i]>=0&&dist[i]<max){
                    u=i;
                    max=dist[i];
                }
            }
        }//找到v距离最短的点
        if(u==v)
            break;//因为本题不一定是连通图，如果在集合外已经没有可达的点了，则中止循环，不必判断完所有点；
        s[u]=1;//把找到的点加入集合，加入后，还没有在集合中的点到v的距离可能因此而改变，所以要修正dist
        for(int i=0;i<n;i++)
            if(s[i]==0&&graph[u][i]>=0)
                if(dist[i]<0||dist[i]>dist[u]+graph[u][i])
                    dist[i]=dist[u]+graph[u][i];
        }
}
int main(){
    int graph[N][N];
    int dist[N];
    int n,q,v,w;
    while(!(cin>>n>>q).eof()){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>graph[i][j];
        for(int i=0;i<q;i++){
            cin>>v>>w;
            shortpath(graph,n,v-1,dist);
            if(dist[w-1]>=0&&v!=w)
                cout<<dist[w-1]<<endl;
            else
                cout<<"jujue"<<endl;
        }
    }
}