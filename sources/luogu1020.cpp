#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n=0,missile[100002],dp[100002];
    memset(dp,0,sizeof(dp));
    int interceptor=0,s,max_interceptor=0;
    missile[n++]=0;
    while(!cin.eof()){
        cin>>missile[n];
        if(!cin.eof()){
            if(missile[n]>missile[n-1]){
                s++;
            }
            n++;
        }
    }
    missile[n]=0;
    for(int i=n-1;i>0;i--){
        for(int j=i+1;j<=n;j++){
            if(missile[j]<=missile[i]){
                dp[i]=max(dp[i],dp[j]+1);
                if(dp[i]>max_interceptor)
                    max_interceptor=dp[i];
            }
        }
        //cout<<dp[i]<<" ";
    }
    cout<<max_interceptor<<endl<<s<<endl;
}