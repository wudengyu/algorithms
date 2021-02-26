#include<iostream>
#include<cstring>
using namespace std;
unsigned long long f[41][41];
int pos[8];
unsigned long long max_product=0;

unsigned long long product(int k){
    unsigned long long result=1;
    for(int i=1;i<=k+1;i++)
        result*=f[pos[i-1]+1][pos[i]];
    return result;
}
void dfs(int depth,int k){
    unsigned long long temp;
    int original=pos[depth];//每次进入，都保存原始位置，返回时还原
    if(depth>1){
        dfs(depth-1,k);//本身不动，向下深搜
        for(int i=pos[depth]+1;i<pos[depth+1];i++){
            pos[depth]=i;//位置向后移
            temp=product(k);
            if(temp>max_product)
                max_product=temp;
            dfs(depth-1,k);//移动后再继续深搜
        }
    }else{
        for(int i=pos[depth]+1;i<pos[depth+1];i++){
            pos[depth]=i;//位置向后移
            temp=product(k);
            if(temp>max_product)
                max_product=temp;
        }
    }
    pos[depth]=original;
} 
int main(){
    int n,k;
    memset(f,0,sizeof(f));
    cin>>n>>k;
    while(getchar()!='\n');
    for(int i=1;i<=n;i++)
        f[i][i]=getchar()-'0';
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            f[i][j]=f[i][j-1]*10+f[j][j];
    }
    for(int i=1;i<=k;i++)
        pos[i]=i;//乘号初始位置
    pos[0]=0;
    pos[k+1]=n;
    dfs(k,k);
    cout<<max_product<<endl;
}