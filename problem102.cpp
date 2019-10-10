/*零崎的朋友很多Ⅲ
 *动态规划-矩阵链乘法
*/
#include <iostream>
using namespace std;
//const int INTMAX=((unsigned)-1)>>1;
const int M=301;
void MATRIX_CHAIN_ORDER(int *p,int length,int dp[][M],int s[][M]){
    int q,n=length-1;
    for(int l=2;l<=n;l++){//矩阵链长度，先计算短的，再计算长的。
        for(int i=1;i<=n-l+1;i++){
            int j=i+l-1;//计算区间[i,j]的最小花费。
            dp[i][j]=INT_MAX;
            for(int k=i;k<=j-l;k++){//k是分割点
		        q=dp[i][k]+dp[k+1][j]+p[i-1]*p[k]*p[j];
		        if(q<dp[i][j]){
		            dp[i][j]=q;
		            s[i][j]=k;
                    cout<<"dp["<<i<<"]["<<j<<"]="<<q<<endl;
		        }
		    }
        }
    }
}
void PRINT_OPTIMAL_PARENS(int s[][M],int i,int j){
	if(i==j)
        cout<<"A"<<i;
	else{
		cout<<"(";
		PRINT_OPTIMAL_PARENS(s,i,s[i][j]);
		PRINT_OPTIMAL_PARENS(s,s[i][j]+1,j);
		cout<<")";
	}
}
int main(){
    int N,p[M],dp[M][M],s[M][M];
    while(!(cin>>N).eof()){
        for(int i=0;i<=N;i++){
            cin>>p[i];
            dp[i][i]=0;//初始化
        }
        MATRIX_CHAIN_ORDER(p,N,dp,s);
        //PRINT_OPTIMAL_PARENS(s,1,N);
    }
    return 0;
}