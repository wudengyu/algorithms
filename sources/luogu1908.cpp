#include<iostream>
using namespace std;
const int N=5e5;
const int MAX=1e9+1;
int s[N];
int inversion=0;
void merge(int arr[],int begin,int middle,int end){
    int *temp=new int[end-begin+1];
    int *left=temp,*left_tail=temp+middle-begin+1;
    int *right=temp+middle-begin+1,*right_tail=temp+end-begin+1;
    for(int i=begin;i<=end;i++)
        *(temp++)=arr[i];
    temp=left;
    for(int k=begin;k<=end;k++){
        if(left<left_tail&&(*left<=*right||right==right_tail))
            arr[k]=*(left++);
        else{
            arr[k]=*(right++);
            inversion+=left_tail-left;
        }
    }
    delete[](temp);
}
void merge_sort(int arr[],int begin,int end){
    if(begin<end){
        int middle=(begin+end)/2;
        merge_sort(arr,begin,middle);
        merge_sort(arr,middle+1,end);
        merge(arr,begin,middle,end);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>s[i];
    merge_sort(s,0,n-1);
    cout<<inversion<<endl;
}