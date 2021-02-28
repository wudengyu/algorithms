#include<iostream>
#include<limits>
using namespace std;
unsigned long long min_v=(long long)(-1)>>(sizeof(unsigned long long)*8-1);
unsigned long long max_v=0;
int n,m,pre_sum=0;
int s[50];
int mod10(int v){
    while(v<0)v+=10;
    return v%10;
}
void dfs(int order,unsigned long long product,int last_pos){
    int sum,tail;
    unsigned long long temp;
    for(int i=last_pos+1;i<n;i++){
        sum=0;
        for(int j=last_pos+1;j<=i;j++)
            sum+=s[j];
        if(order==1){
            pre_sum=sum;
            if(order!=m)
                dfs(order+1,product,i);
            else{
                for(int j=i+1;j<n;j++)
                    sum+=s[j];
                max_v=mod10(sum);
                min_v=max_v;
                break;
            }
        }else if(order!=m){
            dfs(order+1,product*mod10(sum),i);
        }else{
            tail=0;
            for(int j=i+1;j<n;j++)
                tail+=s[j];
            tail+=pre_sum;
            temp=product*mod10(sum)*mod10(tail);
            if(temp<min_v)
                min_v=temp;
            if(temp>max_v)
                max_v=temp;
        }

    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>s[i];
    dfs(1,1,-1);
    cout<<min_v<<endl;
    cout<<max_v<<endl;
}