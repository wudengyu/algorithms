#include<iostream>
#include<cstring>
using namespace std;
int min_v=0x7fffffff;
int max_v=0;
int n,m,start;
int d[101],dp1[101][101][10],dp2[100][100][10];
int main(){
    //memset(data,0,sizeof(data));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>d[i];
        d[n+i]=d[i];
    }
    d[0]=0;
    n*=2;
    for(int i=2;i<n;i++)
        d[i]+=d[i-1];
    for(int i=1;i<n;i++)
        for(int j=i;j<n;j++)
            dp1[i][j][1]=dp2[i][j][1]=((d[j]-d[i-1])%10+10)%10;
    for(int t=2;t<=m;t++){
        for(int i=1;i<=n;i++){
            for(int j=i+t-1;j<=n;j++){
                dp1[i][j][t]=2147483647;
                for(int k=i+t-1;k<=j;k++)
                {
                    int temp=((d[j]-d[k-1])%10+10)%10;
                    dp1[i][j][t]=min(dp1[i][j][t],dp1[i][k-1][t-1]*temp);
                    dp2[i][j][t]=max(dp2[i][j][t],dp2[i][k-1][t-1]*temp);
                }
            }
        }
    }
    n/=2;
    for(int i=1;i<=n;i++)
    {
        max_v=max(dp2[i][i+n-1][m],max_v);
        min_v=min(dp1[i][i+n-1][m],min_v);
    }
   cout<<min_v<<endl;
   cout<<max_v<<endl;
}