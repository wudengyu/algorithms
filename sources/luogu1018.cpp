#include<iostream>
using namespace std;
int s[40];
int pos[8];
long long decompose(int k){
    long long produce=1;
    long long digit[7];
    for(int p=1;p<=k+1;p++){
        long long temp=0;
        for(int q=pos[p-1];q<=pos[p]-1;q++){
            temp=temp*10+s[q];
        }
        digit[p-1]=temp;
    }
    for(int i=0;i<=k;i++)
        produce*=digit[i];
    return produce;
}
void dfs(int mul){
    

} 
int main(){
    int n,k;
    cin>>n>>k;
    while(getchar()!='\n');
    for(int i=0;i<n;i++)
        s[i]=getchar()-'0';
    for(int i=0;i<=k;i++)
        pos[i]=i;//乘号初始位置
    pos[k+1]=n;
    cout<<decompose(k)<<endl;

}