#include<iostream>
using namespace std;
int n,m,ans=0;
void dfs(int k,int pos){
    if(k==m){
        if(pos==1)
            ans++;
        return;
    }
    if((pos>n/2+1?n+1-pos:pos-1)>k){
        return;
    }
    dfs(k+1,pos==n?1:pos+1);
    dfs(k+1,pos==1?n:pos-1);
}
int main(){
    cin>>n>>m;
    dfs(0,1);
    cout<<ans<<endl;
}