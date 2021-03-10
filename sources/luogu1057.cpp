#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int a[31][31];
int main(){
    int temp,ans=0;
    memset(a,0,sizeof(a));
    cin>>n>>m;
    a[0][1]=1;
    for(int i=1;i<=m;i++)
        for(int j=0;j<n;j++)
            a[i][j]+=a[i-1][(j-1+n)%n]+a[i-1][(j+1)%n];
    cout<<a[m][1]<<endl;
}