/*说好的ALS呢？
 *每一个装配环节都有可能在任意一条流水线上完成，不管之前花费大小，不到最后一个环节完成，不能确定总的花费，
 *因为，前面花费大的，往下一个环节的时候也许不需要更换流水线，节约了时间，可能最后总的花费反而小。
 *所以，前面环节的每一种选择路径的花费都需要保存下来。那么，难点就在于：每一个环节结束，将面临n个选择，而
 *环节可能在n条流水线上完成，那么选择下一个环节就有n*n种可能，如果这个数量不减下来，再下一个环节无疑就有n*n*n
 *条路径了。事实上，n*n种可能的路径却最多有n种结果（因为只有n条流水线），所以，可以在n*n条路径中，只保留n条
 *路径。即每条流水线上只保留在此之前最短路径。
 *也就是说，每一条流水线的每一个环节，可能有n条路径可以从上一环节到达，但是只需要保存其中花费最小的一条。其他
 *路径绝对不可能是最优路径。
*/
#include <iostream>
using namespace std;
int pipeline(int p[100][100],int t[100][100],int n,int m,int cost[100][100]){
    int min=(unsigned)-1>>1;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(j==0)
                cost[i][0]=p[i][0];
            else
                cost[i][j]=-1;
    for(int step=1;step<m;step++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(cost[i][step-1]>=0&&(cost[j][step]<0||cost[j][step]>cost[i][step-1]+t[i][j]+p[j][step]))
                    cost[j][step]=cost[i][step-1]+t[i][j]+p[j][step];
    for(int i=0;i<n;i++){
        if(cost[i][m-1]<min)
            min=cost[i][m-1];
    }
    return min;
}
int main(){
    int n,m;
    int p[100][100],t[100][100],cost[100][100];
    while(!(cin>>n>>m).eof()){
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                cin>>p[i][j];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>t[i][j];
        cout<<pipeline(p,t,n,m,cost)<<endl;
    }
}