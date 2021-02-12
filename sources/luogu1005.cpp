#include<iostream>
using namespace std;
const int N=80;
int main(){
    int n,m;
    int matrix[N][N];
    int point[N][2];
    long long ans=0;
    int base=0;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>matrix[i][j];
        }
        point[i][0]=0;
        point[i][1]=m-1;
    }
    for(int j=0;j<m;j++){
        int sum=0;
        base++;
        for(int i=0;i<n;i++){
            if(matrix[i][point[i][0]]<=matrix[i][point[i][1]]){
                sum+=matrix[i][point[i][0]];
                point[i][0]++;
            }else{
                sum+=matrix[i][point[i][1]];
                point[i][1]--;
            }
        }
        ans+=((long long)sum)<<base;
    }
    cout<<ans<<endl;
}