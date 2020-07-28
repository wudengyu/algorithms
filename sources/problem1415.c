#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#define g 3//原根
#define mod 998244353//通常情况下的模数
原根通常都很小，所以原根和模数可以暴力枚举出来，通常取3为原根，模为469762049、998244353、1004535809
*/
const long long g=3;
const long long mod=998244353;
char x[1000001],y[1000001];
int t[40],p[40];
int res[40];

void swap(int *x,int *y){
    int temp=*x;
    *x=*y;
    *y=temp;
}

void reverse(char *s){
    char temp,*end=s;
    while(*end!='\0')end++;
    for(int i=0;i<(end-s)/2;i++){
        temp=*(s+i);
        *(s+i)=*(end-1-i);
        *(end-1-i)=temp;
    }
}

unsigned long long ksm(unsigned long long x, long y) {//快速幂
    unsigned long long p = 1;
    while(y){
        if(y&1)p=x*p%mod;
        x=x*x%mod;
        y>>=1;
    }
    return p;
}
void ntt(int a[],int len,int inv){//把一个多项式由系数形式转换成点集形式或反过来，参数inv指示转换方向
    int bits=0;
    while((1<<bits)<len)bits++;//len的二进制位数
    for(int i=0;i<len;i++){//“位逆序置换”，先计算下标的二进制逆序，下标逆序大于下标的交换
        int t=0;
        for(int j=0;j<bits;j++){
            if(i>>j&1)
                t|=1<<(bits-j-1);
        }
        if(i<t)
            swap(&a[i],&a[t]);
    }
    for(int s=1;s<len;s<<=1){//s是准备合并序列的长度的二分之一
        int w=ksm(g,(mod-1)/(s*2));//原根
        if(inv==-1)                //逆变换
            w=ksm(w,mod-2);
        for(int k=0;k<len;k+=s*2){
            int omega=1;
            for(long long j=0;j<s;j++){
                int t=omega*a[k+j+s]%mod;
                int u=a[k+j];
                a[k+j]=(u+t)%mod;
                a[k+j+s]=(u-t+mod)%mod;
                omega=omega*w%mod;
            }
        }
    }
}
void solve(char c,char d,int length){
    for(int i=0;i<length;i++){
        if(y[i]==c)
            p[i]=1;
        else
            p[i]=0;
        if(x[i]!=d)
            t[i]=1;
        else
            t[i]=0;
    }
    ntt(t,length,1);
    ntt(p,length,1); 
    for(int i=0;i<length;i++) t[i]=t[i]*p[i]; 
    ntt(t,length,-1); 
    for(int i=0;i<length;i++)     
        res[i]+=t[i];     
} 
int main(){
    int l,n,m;
    int ans=0;
    scanf("%d%d\n",&n,&m);
    scanf("%s%s",x,y);
    reverse(y);
    memset(res,0,40*sizeof(int));
    l=1;
    while(l<n+m)l<<=1;
    solve('R','S',l);
    solve('S','T',l);
    solve('T','R',l);
    for (int i=m-1;i<n+m-1;i++){
        if(res[i]>ans)
            ans=res[i];
    }
    printf("%d\n",ans);
    return 0;
}
