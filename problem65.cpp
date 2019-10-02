/*挑战神奇宝贝联盟
 *很明显，以秒为单位，每次都给剩余毒素最多的那只Pockmon用机器解毒，就能保证用时最短；
 *那么，解法自然是用最大堆了。
 *有人采用的办法是找一个中间值，比中间值大的就用机器解，小的就让它自己恢复，第一次找的
 *时候就用中位数，算下来以后不对也没关系，采用类似快排的分治思想，继续在大的一半或者小
 *的一半找。纯算，虽然不能一次算出来，但是感觉类似于快排的效率。而如果采用最大堆模拟解
 *毒过程，不光是要建堆，每解毒1秒，都有一次重新建堆的过程，虽然感觉这样重建堆不会有很多
 *的交换，但是数据多了感觉量也不小，是不是这种简单明了的思路不能在规定时间内跑出来呢？
 *只有试过才知道，所以才做了这个题试一下，结果，时间蛮短的，1000ms的限时才用了4ms，差
 *不多是AC里面的中位数吧，反正不是最大的。
 */
#include <iostream>
using namespace std;
void max_heapify(int a[],int length,int i)
{
    int l=2*i,r=2*i+1,max,temp;
    if(l<=length && a[l]>a[i])
        max = l;
    else
        max =i;
    if(r<=length && a[r]>a[max])
        max = r;
    if(max != i)
    {
        temp=a[i];
        a[i]=a[max];
        a[max]=temp;
        max_heapify(a,length,max);
    }
}
void build_max_heap(int a[],int length){
    for(int i=length/2; i>=1; i--)
        max_heapify(a,length,i);
}
int main(){
    int a[100001],n,k,time;
    while(!(cin>>n).eof()){
        for(int i=1;i<=n;i++)
            cin>>a[i];
        cin>>k;
        build_max_heap(a,n+1);
        time=0;
        while(a[1]>time++){
            a[1]-=k-1;
            max_heapify(a,n+1,1);
        }
        cout<<time-1<<endl;
    }
}