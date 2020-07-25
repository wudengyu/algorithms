#include <stdio.h>
/*
#define g 3//原根
#define mod 998244353//通常情况下的模数
原根通常都很小，所以原根和模数可以暴力枚举出来，通常取3为原根，模为469762049、998244353、1004535809
*/
const int g=3;
const int mod=998244353;
int rev[100000];//整数的二进制倒序表，用于“位逆序置换”

unsigned long long pow(unsigned long long x, long y,long mod) {//快速幂
    unsigned long long p = 1;
    while (y) {
        if (y & 1)p = x * p%mod;
        x = x * x%mod;
        y >>= 1;
    }
    return p;
}
void init_rev(int rev[],int n){//初始化二进制倒序表
    int bit=0;
    while((1<<bit)<n)++bit;
    for(int i=0;i<n;i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }
}
void ntt(int a[],int len,int inv){
    /*把一个多项式由系数形式转换成点集形式或反过来，参数inv指示转换方向
     *数组长度len是2的整数次幂，因为FFT或NTT只能处理长度为2的整数次幂的多项式
    */
    for(int i=0;i<len;i++){//“位逆序置换”
        if (i<rev[i])//if的作用就是只交换逆序的
            swap(a[i],a[rev[i]]);
    }
    
	for (int mid=1;mid<len;mid*=2)
	{
		int tmp=pow(g,(mod-1)/(mid*2));//原根代替单位根
		if (inv==-1)tmp=pow(tmp,mod-2);//逆变换则乘上逆元
		for (int i=0;i<len;i+=mid*2)
		{
			int omega=1;
			for (ll j=0;j<mid;++j,omega=omega*tmp%mod)
			{
				int x=a[i+j],y=omega*a[i+j+mid]%mod;
				a[i+j]=(x+y)%mod,a[i+j+mid]=(x-y+mod)%mod;//注意取模
			}
		}//大体和FFT差不多
	}
}
