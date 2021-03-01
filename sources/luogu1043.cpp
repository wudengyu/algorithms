#include<iostream>
#include<cstring>
using namespace std;
int min_v=0x7fffffff;
int max_v=0;
int n,m,start;
int data[50][50];
int mod10(int v){
    while(v<0)v+=10;
    return v%10;
}
void dfs(int depth,int product,int last_pos){
    int temp;
    if(depth==m){
        for(int i=last_pos+1;i<n;i++){
            if(start==0)
                temp=product*data[last_pos][i-1]*data[i][n-1];
            else
                temp=product*data[last_pos][i-1]*data[i][start-1];
            if(temp>max_v)
                max_v=temp;
            if(temp<min_v)
                min_v=temp;
        }
    }else{
        for(int i=last_pos+1;i<n;i++)
            dfs(depth+1,product*data[last_pos][i-1],i);
    }
}
int main(){
    memset(data,0,sizeof(data));
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
    for(int i=0;i<n-m+1;i++){
        start=i;
        dfs(2,1,start);
    }
   cout<<min_v<<endl;
   cout<<max_v<<endl;
}