#include<iostream>
using namespace std;
int n,a,b,k[201],flag[201];
int dfs(int step,int current){
    int up=-1,down=-1;
    flag[current]=step;
    if(current==b)
        return step;
    /*因为flag是共用，也许之前的递归中到过，但是步数可能更多，应该允许重走*/
    if(current+k[current]<=n&&(flag[current+k[current]]==0||flag[current+k[current]]>=step+1))
        up=dfs(step+1,current+k[current]);
    if(current-k[current]>=1&&(flag[current-k[current]]==0||flag[current-k[current]]>=step+1))
        down=dfs(step+1,current-k[current]);
    if(up==-1)
        return down;
    else if(down==-1)
        return up;
    else
        return min(up,down);
}
int main(){
    for(int i=0;i<=201;i++)
        flag[i]=0;
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)
        cin>>k[i];
    cout<<dfs(0,a)<<endl;
    
}