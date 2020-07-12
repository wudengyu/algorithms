//最优搜索二叉树
#include <iostream>
using namespace std;
const int N=10002;
const int INTMAX=((unsigned)-1)>>1;
float e[N][N],w[N][N];
void OPTIMAL_BST(float p[N],float q[N],int n){
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            if(j==i-1){
                e[i][j]=q[j];
                w[i][j]=q[j];
            }else{
                e[i][j]=0;
                w[i][j]=0;
            }
        }
    }
    for(int l=1;l<=n;l++){
        for(int i=1;i<=n-l+1;i++){
            int j=i+l-1;
            e[i][j]=INTMAX;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int r=i;r<=j;r++){
                float t=e[i][r-1]+e[r+1][j]+w[i][j];
                if(t<e[i][j])
                    e[i][j]=t;
            }
        }
    }

}
int main(){
    int n;
    float p[N],q[N];
    while(!(cin>>n).eof()){
        for(int i=1;i<=n;i++)
            cin>>p[i];
        for(int i=0;i<=n;i++)
            cin>>q[i];
        OPTIMAL_BST(p,q,n);
        cout.setf(ios_base::fixed);
        cout.precision(3);
        cout<<e[1][n]<<endl;
    }
}