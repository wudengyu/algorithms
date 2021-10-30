/* 洛谷P3865 【模板】ST表
 * 题目描述
 * 给定一个长度为N的数列，和M次询问，求出每一次询问的区间内数字的最大值。
 * 输入格式
 * 第一行包含两个整数N,M分别表示数列的长度和询问的个数。
 * 第二行包含N个整数，依次表示数列的第i项。
 * 接下来M行，每行包含两个整数l,r，表示查询的区间为 [l,r]
 * 输出格式
 * 输出包含M行，每行一个整数，依次表示每一次询问的结果。
 * 解题思路
 * 这是一个RMQ(Range Minimum/Maximum Query)问题。
 * 多次查询显示不能多次计算，那样的话，前面的查询对后面的查询没有帮助，只能预处理。。
 * 预处理最直观的办法是把所有可能的区间的最值都事先计算出来，不过这需要N*N的空间，当N很大时不可行。
 * 根据题目标题提示，考虑采用Sparse Table（稀疏表），即：对于每一个区间的起点i,
 * 并不去计算所有可能的终点(n-i+1个)，而只是计算以i，i+2^0，i+2^1，…为终点的区间，这样预处理需要的空间就只需要N*logN
 * 当然，这样处理，查询时就不能直接找到对应的区间，但是也不难，因为对于待查询的区间[l,r]来说
 * 总是可以找到区间[l,l+2^x]和[r-2^y,r]这样的两个区间的，它们中的最大值就是区间[l,r]的最大值
 * 这两个区间的大小一定是2的整数次方，所以前面表达为l+2^x和r-2^y，且l+2^x<=r，r-2^y>=l，当然还要有r-2^y<=l+2^x+1
 * 所以，x、y可以取log(r-l)
 * 再看ST表怎么预先填充，这实际上是一个DP问题，设st[i][j]为区间[i,i+2^j-1]的最大值，显然st[i][0]=a[i]
 * st[i][j]是一个长度为2^j-1的区间，可以分解为两个只有一半长度的区间，[i,i+2^(j-1)-1]和[i+2^(j-1),i+2^j-1]
 * 前一个的最大值是st[i][j-1]，后一个的最大值是st[i+2^(j-1)][j-1]，
 * 列下标计算下来就是j-1，但其实不用算，因为列下标是由区间的长度决定的，显然就应该是j-1。
 * 填充st的时候，就按st[1][0]、st[2][0]、……、st[1][1]、st[2][1]、……逐列填充
*/
#include <iostream>
using namespace std;
const int N=100000;
int a[N+1]={0},st[N+1][18];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int search(int l,int r){
    if(l==r)
        return st[l][0];
    int k=0,e=1;
    while(e<r-l+1){
        e<<=1;
        k++;
    }//e=2^k>=length
    return max(st[l][k-1],st[r-e/2+1][k-1]);
}
int main(){
    int n,m,l,r;
    n=read();
    m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        st[i][0]=a[i];
    }
    for(int j=1,e=1;e<n;j++,e<<=1)//e=2^(j-1)
        for(int i=1;i<=n;i++)
            if(i+e<=n)
                st[i][j]=max(st[i][j-1],st[i+e][j-1]);
    for(int i=0;i<m;i++){
        l=read();
        r=read();
        printf("%d\n",search(l,r));
    }
}