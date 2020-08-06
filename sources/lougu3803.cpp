#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
const int mod=998244353;

int p[2097152],g[2097152];//两多项式最高可达2*10^6次，系数则有2*10^6+1项，但是傅里叶变换需要把系数扩展到2的整数次方，所有这里预留的2^21，大多数是直接扩展4倍。
unsigned long long pow(unsigned long long x,int y,int mod){
    unsigned long long p=1;
    while(y){
        if(y&1)p=x*p%mod;
        x=x*x%mod;
        y>>=1;
    }
    return p;
}
void ntt(int a[],int len,int inv){
    for(int i=0,j=0;i<len;i++){//采用雷德算法进行位逆序变换，很多写法i直接从1开始，因为0显然是不需要变换位置，所以不影响结果。
        int k=len;//len是2的整数次幂，决定了二进制的位数；
        if(i<j)swap(a[i],a[j]);
        //以下计算j按二进制逆序的下一个数，从最高位加起，向右进位
        while(j&(k>>=1))j&=~k;//这一步在很多代码中用算术运算代替逻辑运算（右移就是除以2，位与可以用大于来判断）结果是一样的，但是就不太好理解了。
        j|=k;//前一步只是处理了需要进位的，不需要进位之后，置1（或运算）
    }
    for(int s=2;s<=len;s<<=1){//s是准备合并序列的长度
        unsigned long long wm=pow(3,(mod-1)/s);
        if(inv==-1)wm=pow(wm,mod-2);
        for(int k=0;k<len;k+=s){//步长是序列的长度，循环一次处理一个序列
            int w=1;
            for(int j=0;j<s/2;j++){//前一半和后一半合并，所以循环终止条件是到k+s/2
                unsigned long long t=(unsigned long long)w*a[k+j+s/2]%mod;
                unsigned long long u=a[k+j];
                a[k+j]=(u+t)%mod;
                a[k+j+s/2]=(u-t+mod)%mod;
                w=(unsigned long long)w*wm%mod;
            }
        }
    }
    if(inv==-1){
        unsigned long long t=pow(len,mod-2);
        for(int i=0;i<len;i++)
            a[i]=a[i]*t%mod;
    }
}
int main(){
    int n,m,limit=1,temp;
    cin>>n>>m;
    while(limit<n+m+1)limit<<=1;
    for(int i=0;i<=n;i++)
        cin>>p[i];
    for(int i=0;i<=m;i++)
        cin>>g[i];
    for(int i=n+1;i<limit;i++)
        p[i]=0;
    for(int i=m+1;i<limit;i++)
        g[i]=0;
    ntt(p,limit,1);
    ntt(g,limit,1);
    for(int i=0;i<limit;i++){
        p[i]=(unsigned long long)p[i]*g[i]%mod;
        cout<<"p["<<i<<"]="<<p[i]<<",g["<<i<<"]="<<g[i]<<" ";
    }
    ntt(p,limit,-1);
    for(int i=0;i<n+m+1;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
}