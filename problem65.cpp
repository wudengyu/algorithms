#include <iostream>
using namespace std;
int a[1000000001],length;
void max_heapify(int length,int i)
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
        max_heapify(length,max);
    }
}
void build_max_heap(int length){
    for(int i=length/2; i>=1; i--)
        max_heapify(length,i);
}
int main(){
    int n,k,time=0;
    while(!(cin>>n).eof()){
        for(int i=1;i<=n;i++)
            cin>>a[i];
        cin>>k;
        build_max_heap(n+1);
        for(int i=1;i<=n;i++)
            cout<<a[i]<<' ';
        while(a[1]>time++){
            a[1]-=k;
            max_heapify(n+1,1);
        }
        cout<<time;
    }
}