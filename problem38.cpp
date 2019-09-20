#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;
typedef long long ll;
int length;
void MIN_HEAPIFY(int A[],int i)
{
    int l=2*i,r=2*i+1,min,temp;
    if(l<=length && A[i]>A[l])
        min = l;
    else
        min =i;
    if(r<=length && A[min]>A[r])
        min = r;
    if(min != i)
    {
        temp=A[i];
        A[i]=A[min];
        A[min]=temp;
        MIN_HEAPIFY(A,min);
    }
}
void build_min_heap(int A[])
{
    for(int i=(int)floor(length/2); i>=1; i--)
    {
        MIN_HEAPIFY(A,i);
    }
}
int heapsort(int A[])
{
    int B[3]= {0};
    build_min_heap(A);
    while(1)
    {
        for(int i=1; i<=2; i++)
        {
            int temp=A[1];
            A[1]=A[length];
            A[length]=temp;
            B[i]=A[length];
            length--;
            MIN_HEAPIFY(A,1);
        }
        B[0] += B[1]+B[2];
        if(length == 0)
            break;
        length++;
        A[length]=B[1]+B[2];
        for(int i=length; i>1 && A[i]<A[(int)floor(i/2)]; i=floor(i/2))
        {
            int temp=A[i];
            A[i]=A[(int)floor(i/2)];
            A[(int)floor(i/2)]=temp;
        }
    }
    return B[0];

}
int main()
{
    cin >> length;
    int A[length+1];
    for(int i=1; i<=length; i++)
        cin >> A[i];
    cout << heapsort(A) << endl;

    return 0;
}
  
