#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int K=20,N=1000;
const int inf=0x7f7f7f7f;
class flowedge{
    private:
    int m_v;
    int m_w;
    int m_capacity;
    int m_flow=0;
    int m_next;
    public:
    flowedge(){};
    flowedge(int v,int w,int capacity){
        m_v=v;
        m_w=w;
        m_capacity=capacity;
    };
    int from(){return m_v;}
    int to(){return m_w;}
    int capacity(){return m_capacity;}
    int flow(){return m_flow;}

    int residualCapacityTo(int vertex){
        if(vertex==m_v)return m_flow;
        else if(vertex==m_w) return m_capacity-m_flow;
        else return 0;
    };

    void addResidualFlowTo(int vertex,int delta){
        if(vertex==m_v) m_flow-=delta;
        else if(vertex==m_w) m_flow+=delta;
    };
}e[K*N+1];
vector<flowedge> graph[K+N+2];
int start=0,target=K+N+1;//起点和终点索引
int dist[K+N+2];//用于保存bfs遍历值（分层）
int ans=0;
bool bfs(int s,int t){
    int visit[K+N+2]={};
    memset(dist,0x7f,sizeof dist);
    queue<int> q;
	dist[s] = 0;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for(auto p:graph[u]){
			int v=p.to();
			if(dist[v]>dist[u]+1&&p.residualCapacityTo(v)>0){
                dist[v]=dist[u]+1;
				if(!visit[v]){
                    q.push(v);
                    visit[v]=true;
                }
			}
		}
	}
	return dist[t]!=0x7f7f7f7f;
}
int update(int s,int t,flowedge *pathTo[],int cf){
    int current=t;
    while(current!=s){
        pathTo[current]->addResidualFlowTo(current,cf);
        current=pathTo[current]->from();
    }
    return cf;
}
int dfs(int s,int t){
    int cf[K+N+2]={}; //当前寻路过程中，到达顶点的最小残余流量
    int marked[2*(N+1)]={};
    flowedge *pathTo[K+N+2]={};//到达节点的边的指针
    cf[s]=inf;
    marked[s]=1;
    queue<int> q;
    q.push(s);
	if(s==t)
        return 0;
    while(!q.empty()&&marked[t]==0){
        int current=q.front();
        q.pop();
	    for(auto p:graph[current]){
            int v=p.to();
		    if(marked[v]==0&&dist[v]==dist[current]+1&&p.residualCapacityTo(v)>0){//只考虑下一层的点
                marked[v]=1;
                pathTo[v]=&p;
                cf[v]=min(cf[current],p.residualCapacityTo(v));
                q.push(v);
			}
		}
	}
    if(marked[t]==1){
        update(s,t,pathTo,cf[t]);
        return 1;
    }else
        return 0;
}
int dinic(){
	int minflow = 0;
	while(bfs(start,target)){
		while(minflow=dfs(start,target))
			ans+=minflow;
	}
	return ans;
}
int main(){
    int k,n,p,temp;
    cin>>k>>n;
    for(int i=1;i<=k;i++){
        cin>>temp;
        graph[start].push_back(flowedge(start,i,temp));
    }
    for(int i=1;i<=n;i++){
        cin>>p;
        for(int j=0;j<p;j++){
            cin>>temp;
            graph[temp].push_back(flowedge(temp,k+i,1));
        }
        graph[k+i].push_back(flowedge(k+i,target,1));
    }
    cout<<dinic()<<endl;
	return 0;
}