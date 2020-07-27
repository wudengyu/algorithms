#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,m,i=0,j=0,max_win=0;
    char c,xg[100000],yj[100000];
    scanf("%d%d\n",&n,&m);
    while((c=getchar())!='\n'){
        xg[i++]=c;
    }
    while((c=getchar())!='\n'){
        switch(c){
            case 'R':
                yj[j++]='S';
                break;
            case 'S':
                yj[j++]='P';
                break;
            case 'P':
                yj[j++]='R';
                break;
        }
    }
    for(int i=0;i<n;i++){
        int temp_win=0;
        for(int j=0;j<m&&i+j<n;j++)
            if(xg[i+j]==yj[j])
                temp_win++;
        if(temp_win>max_win)
            max_win=temp_win;
    }
    printf("%d\n",max_win);
}
#include <string.h>
/*
#define g 3//原根
#define mod 998244353//通常情况下的模数
原根通常都很小，所以原根和模数可以暴力枚举出来，通常取3为原根，模为469762049、998244353、1004535809
*/
const long long g=3;
const long long mod=998244353;
const int N=1<<22;
int t[4000005],p[4000005];
char xg[1000001],yj[1000001];
int rev[100000];//整数的二进制倒序表，用于“位逆序置换”

int ans[100000]={0};
void reverse(char *s){
    char temp,*begin=s;
    int length=0;
    while(*(s++)!='\0')length++;
    for(int i=0;i<length/2;i++){
        temp=*(begin+i);
        *(begin+i)=*(begin+length-1-i);
        *(begin+length-1-i)=temp;
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
    int length=1;
    while(length<len)length<<=1;//计算不小于len的2的整数次幂
    int *ar=(int *)malloc(length*sizeof(int));//len不一定是2的整数次幂，所以申请一个新的数组
    memset(ar,0,length*sizeof(int));
    for(int i=0;i<len;i++){//“位逆序置换”:把原数组按置换后的位置复制到新数组
        ar[rev[i]]=a[i];
    }
    for(int s=1;s<length;s<<1){//s是准备合并序列的长度的二分之一
        int w=ksm(g,(mod-1)/(s*2));//原根
        if(inv==-1)                //逆变换
            w=ksm(w,mod-2);
        for(int k=0;k<length;k+=s*2){
            int omega=1;
            for(long long j=0;j<s;j++){
                int t=omega*ar[k+j+s]%mod;
                int u=ar[k+j];
                ar[k+j]=(u+t)%mod;
                ar[k+j+s]=(u-t+mod)%mod;
                omega=omega*w%mod;
            }
        }
    }
}
void solve(char c,int length){
    for(int i=0;i<length;i++){
        if(xg[i]==c)
            t[i]=1;
        else
            t[i]=0;
        if(yj[i]==c)
            p[i]=1;
        else
            p[i]=0;
    }
    fft(t,length,1);
    fft(p,length,-1); 
    for(int i=0;i<length;i++) t[i]=t[i]*p[i]; 
    fft(t,length,-1); 
    for(int i=0;i<length;i++) 
        sum[i]= (int)(f[i].r / n + 0.5); 
    for(int i = 0;i < n;i++)     
        res[i] += sum[i];     
} 
*/
int main(){
    int n,m,pos,bits;
    char c;
    scanf("%d%d\n",&n,&m);
    scanf("%s%s",xg,yj);
    for(int i=0;i<m;i++){
        if(yj[i]=='R')
            yj[i]='S';
        else if(yj[i]=='S')
            yj[i]='T';
        else
            yj[i]='R';
    }
    reverse(yj);
    /*
    pos=0;
    while((c=getchar())!='\n'){
        switch(c){
            case 'R':
                t[0][pos++]=1;
                break;
            case 'S':
                t[1][pos++]=1;
                break;
            case 'T':
            default:
                t[2][pos++]=1;
                break;
        }
    }
    pos=0;
    while((c=getchar())!='\n'){
        switch(c){
            case 'R':
                p[1][pos++]=1;
                break;
            case 'S':
                p[2][pos++]=1;
                break;
            case 'T':
            default:
                p[0][pos++]=1;
                break;
        }
    }
    //初始化二进制倒序表，“位逆序置换”时用
    bits=0;//模板字符串长度的二进制位数
    while((1<<bits)<m)bits++;
    for(int i=0;i<(1<<bits);i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bits-1));
    }
    for(int i=0;i<3;i++){
        int *tmp1=ntt(p[i],m,1);
        for(int j=0;j<n;j++){
            int *tmp2=ntt(&t[i][j],j+m<n?m:n-j,1);
        }
    }
    */

}
