#include<iostream>
#include<cstring>
using namespace std;
unsigned long long min_v=(long long)(-1)>>(sizeof(unsigned long long)*8-1);
unsigned long long max_v=0;
int n,m;
int data[50][50];
unsigned long long dp_min[10][50][50],dp_max[10][50][50];
int mod10(int v){
    while(v<0)v+=10;
    return v%10;
}
int main(){
    memset(data,0,sizeof(data));
    memset(dp_min,0xff,sizeof(dp_min));
    memset(dp_max,0,sizeof(dp_max));
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>data[i][i];
    for(int i=0;i<n;i++){
        data[i][i]=mod10(data[i][i]);
        for(int j=i+1;j!=i;j++){
            if(i==0&&j==n)
                break;
            else if(j==n){
                j=0;
                data[i][j]=mod10(data[i][n-1]+data[j][j]);
            }else
                data[i][j]=mod10(data[i][j-1]+data[j][j]);
        }
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dp_min[1][i][j]=dp_max[1][i][j]=data[i][j];//初始化，i,j之间分为1个部分时的积
}