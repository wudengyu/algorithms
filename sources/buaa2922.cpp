#include<iostream>
#include<vector>
#include<forward_list>
using namespace std;
struct egde{
    int vertex;
    int cost;
};
Dijkstra
int main(){
    int n,m;
    int a,b,d;
    cin>>n>>m;
    forward_list<egde> *graph[n+1];
    int vomit[n+1];
    for(int i=1;i<=n;i++)
        graph[i]=new forward_list<egde>();
    for(int i=0;i<m;i++){
        cin>>a>>b>>d;
        graph[a]->push_front({b,d});
        graph[b]->push_front({a,d});
    }
    for(int i=1;i<=n;i++)
        cin>>vomit[i];
}