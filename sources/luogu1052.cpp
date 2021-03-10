#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int stone[100],f[10];
int binary(int *s,int begin,int end,int value){
    int mid=begin+(end-begin)/2;
    if(begin>end)
        return -1;
    if(*(s+mid)==value)
        return mid;
    else if(*(s+mid)>value)
        return binary(s,begin,mid-1,value);
    else
        return binary(s,mid+1,end,value);
}
int find(int *s,int begin,int end,int value){
    while(begin<end&&*(s+begin)<value)begin++;
    return begin;
}
int main(){
    int l,s,t,m,temp,pos=0;
    memset(stone,0,sizeof(stone));
    memset(f,0x7f,sizeof(f));
    cin>>l>>s>>t>>m;
    for(int i=0;i<m;i++)
        cin>>stone[i];
    sort(stone,stone+m);
    f[0]=0;
    for(int i=1;i<=l;i++){
        temp=1e9;
        for(int j=i-s;j>=0&&i-j<=t;j--)
            temp=min(temp,f[j%10]);
        pos=find(stone,pos,m-1,i);
        if(stone[pos]==i)
            f[i%10]=temp+1;
        else
            f[i%10]=temp;
    }
    cout<<f[l%10]<<endl;
    for(int i=0;i<m;i++)
        cout<<stone[i]<<" ";
}