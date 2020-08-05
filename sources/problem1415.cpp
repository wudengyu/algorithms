#include <iostream>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=2<<20; //一般开出4倍空间，实际最大可能用到2倍再扩展到2的整数次方，所以这里取2^21
char x[N],y[N];
complex<double> f[N], g[N];
int sum[N];
void fft(complex<double> a[],int len,int inv){
    for(int i=0,j=0;i<len;i++){//采用雷德算法进行位逆序变换，很多写法i直接从1开始，因为0显然是不需要变换位置，所以不影响结果。
        int k=len;//len是2的整数次幂，决定了二进制的位数；
        if(i<j)swap(a[i],a[j]);
        //以下计算j按二进制逆序的下一个数，从最高位加起，向右进位
        while(j&(k>>=1))j&=~k;//这一步在很多代码中用算术运算代替逻辑运算（右移就是除以2，位与可以用大于来判断）结果是一样的，但是就不太好理解了。
        j|=k;//前一步只是处理了需要进位的，不需要进位之后，置1（或运算）
    }
    for(int s=2;s<=len;s<<=1){//s是准备合并序列的长度
        complex<double> wm(cos(inv*2*M_PI/s),sin(inv*2*M_PI/s));
        for(int k=0;k<len;k+=s){//步长是序列的长度，循环一次处理一个序列
            complex<double> w(1,0);
            for(int j=0;j<s/2;j++){//前一半和后一半合并，所以循环终止条件是到k+s/2
                complex<double> t=w*a[k+j+s/2];
                complex<double> u=a[k+j];
                a[k+j]=u+t;
                a[k+j+s/2]=u-t;
                w=w*wm;
            }
        }
    }
    if(inv==-1)
        for(int i=0;i<len;i++)
            a[i].real(a[i].real()/len);
}
void solve(char c,int n,int m,int len){
    for(int i=0;i<n;i++){
        if(x[i]==c)
            f[i].real(1);
        else
            f[i].real(0);
        f[i].imag(0);
    }
    for(int i=n;i<len;i++){
        f[i].real(0);
        f[i].imag(0);
    }
    for(int i=0;i<m;i++){
        if(y[i]==c)
            g[i].real(1);
        else
            g[i].real(0);
        g[i].imag(0);
    }
    for(int i=m;i<len;i++){
        g[i].real(0);
        g[i].imag(0);
    }
    fft(f,len,1);
    fft(g,len,1);
    for(int i=0;i<len;i++)
        f[i]=f[i]*g[i];
    fft(f,len,-1);
    for(int i=0;i<len;i++)
        sum[i]+=(int)(f[i].real()+0.5);
}
int main(){
    int n,m,len=1,ans=0;
    scanf("%d%d",&n,&m);
    scanf("%s%s",x,y);
    for (int i=0;i<m;i++){
        switch(y[i]){
            case 'R':
                y[i]='S';
                break;
            case 'S':
                y[i]='P';
                break;
            case 'P':
                y[i]='R';
        }
    }
    reverse(y,y+m);
    while(len<n+m-1)len<<=1;
    solve('R',n,m,len);
    solve('S',n,m,len);
    solve('P',n,m,len);
    for(int i=m-1;i<n+m-1;i++)
        ans=max(ans,sum[i]);
    printf("%d\n",ans);
    return 0;
}