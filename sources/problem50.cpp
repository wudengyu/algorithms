//找出n个数中第k大的数
/*选择排序和插入排序性能明显不行，考虑堆排序和快速排序
 *然而堆排序也TLE，所以采用快速排序，快排效率又跟选择分割的参考值有很大关系，但是随机取都TLE，
 *
*/
#include <iostream>
using namespace std;
int select(int* a,int n,int k){
    int pivot;
    int lo=0,hi=n-1;
    int i,j;
    while(hi>lo){
        pivot=a[k-1];
        i=lo;
        j=hi;
        while(i<j){
            while(a[i]>pivot)
                i++;
            while(a[j]<pivot)
                j--;
            if(i<j){
                int tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
            }
        }
        if(i==k-1) return a[k-1];
        else if(i<k-1) lo=i;
        else if(i>k-1) hi=j;
    }
    return a[k-1];
}
int main(){
    int n,k,s[1000000];
    while(cin>>n>>k){
        for(int i=0;i<n;i++)
            cin>>s[i];
        cout<<select(s,n,k)<<endl;
    }
}