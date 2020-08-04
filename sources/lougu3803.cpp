#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

complex<double> p[2097152],g[2097152];//两多项式最高可达2*10^6次，系数则有2*10^6+1项，但是傅里叶变换需要把系数扩展到2的整数次方，所有这里预留的2^21，大多数是直接扩展4倍。
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
int main(){
    int n,m,limit=1,temp;
    cin>>n>>m;
    while(limit<n+m+1)limit<<=1;
    for(int i=0;i<=n;i++){
        cin>>temp;
        p[i].real(temp);
        p[i].imag(0);
    }
    for(int i=0;i<=m;i++){
        cin>>temp;
        g[i].real(temp);
        g[i].imag(0);
    }
    for(int i=n+1;i<limit;i++){
        p[i].real(0);
        p[i].imag(0);
    }
    for(int i=m+1;i<limit;i++){
        g[i].real(0);
        g[i].imag(0);
    }
    fft(p,limit,1);
    fft(g,limit,1);
    for(int i=0;i<limit;i++){
        p[i]=p[i]*g[i];
    }
    fft(p,limit,-1);
    for(int i=0;i<n+m+1;i++){
        cout<<(int)(p[i].real()+0.5)<<" ";
    }
    cout<<endl;
}