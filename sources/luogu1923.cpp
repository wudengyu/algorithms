#include<iostream>
#include<cstdio>
using namespace std;
const int N=5000000;
int a[N];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void insert_sort(int arr[],int begin,int end){
    for(int i=begin;i<=end;i++){
        for(int j=i;j>begin&&arr[j]<arr[j-1];j--){
            swap(arr+j,arr+j-1);
        }
    }
}
int quick_find(int arr[],int begin,int end,int nth){
    if(end<=begin){
        //insert_sort(arr,begin,end);
        return arr[nth];
    }else{
        int u=rand()%(end-begin+1)+begin;
        int v=arr[u];
        swap(arr+begin,arr+u);
        int i=begin;
        int j=end+1;
        while(1){
            while(arr[++i]<v)if(i==end)break;
            while(arr[--j]>=v)if(j==begin)break;
            if(i>=j)break;
            swap(arr+i,arr+j);
        }
        swap(arr+begin,arr+j);
        if(j==nth)
            return arr[j];
        else if(j>nth)
            return quick_find(arr,begin,j-1,nth);
        else
            return quick_find(arr,j+1,end,nth); 
    }
}
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    cout<<quick_find(a,0,n-1,k)<<endl;
}