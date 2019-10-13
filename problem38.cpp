#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;
const int INTMAX=((unsigned)-1)>>1;
void min_heapify(int a[],int length,int i){
    int l=2*i,r=2*i+1,min,temp;
    if(l<=length&&a[i]>a[l])
        min=l;
    else
        min=i;
    if(r<=length&&a[min]>a[r])
        min = r;
    if(min!=i){
        temp=a[i];
        a[i]=a[min];
        a[min]=temp;
        min_heapify(a,length,min);
    }
}
void build_min_heap(int a[],int length){
    for(int i=length/2;i>=1;i--)
        min_heapify(a,length,i);
}
int heapsort(int a[],int length)
{
    int b[3]= {0};
    build_min_heap(a,length);
    while(1){
        for(int i=1;i<=2;i++){
            int temp=a[1];
            a[1]=a[length];
            a[length]=temp;
            b[i]=a[length];
            length--;
            min_heapify(a,length,1);
        }
        b[0]+=b[1]+b[2];
        if(length==0)
            break;
        length++;
        a[length]=b[1]+b[2];
        for(int i=length;i>1&&a[i]<a[i/2];i/=2){
            int temp=a[i];
            a[i]=a[i/2];
            a[i/2]=temp;
        }
    }
    return b[0];
}
int main(){
    int n,*a;
    while(!(cin>>n).eof()){
        a=new int[n+1];
        for(int i=1;i<=n;i++)
            cin>>a[i];
        cout<<heapsort(a,n)<<endl;
        delete[] a;
    }
    return 0;
}
  
