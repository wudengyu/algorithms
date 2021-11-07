/*洛谷 P2472 [SCOI2007]蜥蜴
 *题目描述
 *在一个r行c列的网格地图中有一些高度不同的石柱，第i行j列的石柱高度为h_{i,j}。
 *一些石柱上站着一些蜥蜴，你的任务是让尽量多的蜥蜴逃到边界外。
 *每行每列中相邻石柱的距离为1，蜥蜴的跳跃距离是d，即蜥蜴可以跳到平面距离不超过d的任何一个石柱上。
 *石柱都不稳定，每次当蜥蜴跳跃时，所离开的石柱高度减1（如果仍然落在地图内部，则到达的石柱高度不变）。
 *如果该石柱原来高度为1，则蜥蜴离开后消失，以后其他蜥蜴不能落脚。
 *任何时刻不能有两只蜥蜴在同一个石柱上。
 *解题思路
 *最开始的想法是把石柱当成通道，但是这样确定不了正向流和反向流；但是拆点法就没这个问题，把每个点拆成入点和出点
 *连到其他点总是用出点去连，而连其他点是没有流量限制的，无所谓正、反
 *此题传统Bellman-Ford算法可过，但是由于在最后在计算最大流时犯了个错误，一直没查出来
 *所以又参考别人的题解用dinic重写，但是这段代码里面用了递归，所以实际运行时间更长，当然，这不是dinic算法的问题，
 *而是实现问题，不是用递归来更新流，而是记录路径，再更新流明显好得多，下次再做最大流之类的题再写了。
*/
#include <iostream>
#include <queue>
using namespace std;
const int R=20,C=20;
int tail,head[2*R*C+3],current[2*R*C+3];//current用于dfs时记录已经访问到的点，每次bfs时重新与head同步
int start=0,target;//起点和终点
long long ans;
struct edge{
    int from;
    int to;
    int capacity;
    int next;
}e[R*C*R*C];
int dist[2*R*C+3];
void add_edge(int from,int to,int capacity){
    e[tail].from=from;
    e[tail].to=to;
    e[tail].capacity=capacity;
    e[tail].next=head[from];
    head[from]=tail;
    tail++;
}
bool bfs(int s,int t){
    int visit[2*R*C+3]={};
    queue<int> q;
	for(int i = 0; i <= t; i++){
        visit[i]=0;
        dist[i]=__INT_MAX__;
        current[i]=head[i];
    }
	dist[s] = 0;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(dist[v]>dist[u]+1&&e[i].capacity>0){
                dist[v]=dist[u]+1;
				if(!visit[v]){
                    q.push(v);
                    visit[v]=true;
                }
			}
		}
	}
	return dist[t]!=__INT_MAX__;
}
/*此函数递归调用，返回时即可延途更新流*/
int dfs(int u,int flow){
	int res = 0;
	if(u==target) return flow;
	for(int i=current[u];i;i=e[i].next){
		current[u] = i;
		int v = e[i].to;
		if(dist[v]==dist[u]+1&&e[i].capacity){//只考虑下一层的点
			if(res=dfs(v,min(flow,e[i].capacity))){
				e[i].capacity-=res;
				e[i^1].capacity+=res;
				return res;
			}
		}
	}
	return 0;
}
int dinic(){
	int minflow = 0;
	while(bfs(start,target)){
		while(minflow=dfs(start,0x7fffffff))
			ans+=minflow;
	}
	return ans;
}
int main(){
    int r,c,d;
    int count=0;//蜥蜴的数量
    char ch;
    int matrix[R+1][C+1]={};
    tail=2;//边表的尾后指针，即从2开始
    cin>>r>>c>>d;
    target=2*r*c+1;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>ch;
            matrix[i][j]=ch-'0';
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>ch;
            if(ch=='L'){
                count++;
                add_edge(start,(i-1)*c+j,1);
                add_edge((i-1)*c+j,start,0);
            }
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(matrix[i][j]){
                add_edge((i-1)*c+j,r*c+(i-1)*c+j,matrix[i][j]);
                add_edge(r*c+(i-1)*c+j,(i-1)*c+j,0);
                if(i-d<=0||i+d>r||j-d<=0||j+d>c){
                    add_edge(r*c+(i-1)*c+j,target,__INT_MAX__);
                    add_edge(target,r*c+(i-1)*c+j,0);
                }
                for(int x=i-d;x<=i+d;x++){
                    for(int y=j-d;y<=j+d;y++){
                        if(matrix[x][y]&&(x!=i||y!=j)&&x>0&&x<=r&&y>0&&y<=c&&((x-i)*(x-i)+(y-j)*(y-j)<=d*d)){
                            add_edge(r*c+(i-1)*c+j,(x-1)*c+y,__INT_MAX__);
                            add_edge((x-1)*c+y,r*c+(i-1)*c+j,0);
                        }
                    }
                }
            }
        }
    }
    cout<<count-dinic()<<endl;
	return 0;
}