#include<iostream>
#include<vector>
#include<list>
#include<queue>
using namespace std;
struct edge{
    int to;
    long long cost;
    edge(){};
    edge(int to,long long cost){
        this->to=to;
        this->cost=cost;
    };
};
struct node{
    int indegree=0;
    int outdegree=0;
    long long c;
    long long u;
    long long sum;
    node(){};
    node(long long c,long long u){
        this->c=c;
        this->u=u;
    };
};
int main(){
    vector<list<edge>> graph(101);
    vector<node> s(101);
    queue<int> q;
    long long n,p,c,u,outsum=0;
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        long long c,u;
        cin>>s[i].c>>s[i].u;
    }
    for(int k=0;k<p;k++){
        int i,j;
        long long w;
        cin>>i>>j>>w;
        graph[i].push_back(edge(j,w));
        s[i].outdegree+=1;
        s[j].indegree+=1;
    }
    for(int i=1;i<=n;i++){
        if(s[i].indegree==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int current=q.front();
        q.pop();
        if(s[current].outdegree==0&&s[current].c>0){
            cout<<current<<" "<<s[current].c<<endl;
            outsum+=1;
        }
        else if(s[current].outdegree>0){
            for(auto i=graph[current].begin();i!=graph[current].end();i++){
                s[i->to].sum+=i->cost*s[current].c;
                s[i->to].indegree-=1;
                if(s[i->to].indegree==0){
                    s[i->to].c=s[i->to].sum>s[i->to].u?s[i->to].sum-s[i->to].u:0;
                    q.push(i->to);
                }
            }
        }
    }
    if(outsum==0){
        cout<<"NULL"<<endl;
    }
}