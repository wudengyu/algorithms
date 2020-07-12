/*DP大作战—组合背包*/
#include <iostream>
#include <cstring>
using namespace std;
int dp[30001];
int V,N;//背包容量、物体种类数
struct {
    int value;
    int pos;
}que[30001];
void CompletePack(int w,int v){
    for(int i=w;i<=V;i++)
        if(dp[i]<dp[i-w]+v)
            dp[i]=dp[i-w]+v;
}
void ZeroOnePack(int w,int v){
    for(int i=V; i>=w; i--)
        if(dp[i]<dp[i-w]+v)
            dp[i]=dp[i-w]+v;
}
void MultiplePack(int w,int v,int m){
    for(int r=0;r<w;r++){//枚举余数 
        int head=0,tail=0;//队列初始化 
        for(int k=0;k<=(V-r)/w;k++){
            int x=k;
            int y=dp[k*w+r]-k*v;
            while(head<tail&&que[head].pos<k-m)head++;//限制长度
            while(head<tail&&que[tail-1].value<=y)tail--;
            que[tail].value=y,que[tail].pos=x;
            tail++;
            dp[k*w+r]=que[head].value+k*v;
        }
    }
}
int main(){
    int n,v,w,m;//v物品价值，w物品重量，m物品件数
    cin>>n;
    while(n--){
        memset(dp,0,sizeof(dp));
        cin>>V>>N;
        for(int i=0;i<N;i++){
            cin>>v>>w>>m;
            if(m==1)
                ZeroOnePack(w,v);
            else if(w*m>=V||m==233)
                CompletePack(w,v);
            else
                MultiplePack(w,v,m);
        }
        cout<<dp[V]<<endl;
    }
}