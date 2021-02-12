#include<iostream>
#include<cstring>
using namespace std;
const int N=10;
int main(){
    unsigned int matrix[N][N];
    memset(matrix,0,sizeof(unsigned int)*N*N);
    int n,x,y,z;
    cin>>n;
    while(1){
        cin>>x>>y>>z;
        if(x==0&&y==0&&z==0)
            break;
        matrix[x-1][y-1]=z;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
}