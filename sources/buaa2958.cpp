#include<iostream>
using namespace std;
int arr[100000],start[100000],tally[100000];
int find(int value,int begin,int end){
    if(begin>end)
        return -1;
    int mid=begin+(end-begin)/2;
    if(arr[mid]==value)
        return mid;
    else{
        if(value<arr[mid])
            return find(value,begin,mid-1);
        else
            return find(value,mid+1,end);
    }
}
int main(){
    int n,q,x,point,tmp;
    int previous_value=-1,previous_position=0;
    for(int i=0;i<100000;i++){
        arr[i]=0;
        start[i]=0;
        tally[i]=0;
    }
    cin>>n;
    point=0;
    for(int i=1;i<=n;i++){
        cin>>tmp;
        if(tmp==previous_value)
            tally[point]++;
        else{
            tally[++point]++;
            previous_value=tmp;
        }
        if(i>0&&arr[i-1]==arr[i])
            start[i]=start[i-1];
        else
            start[i]=i;
        for(int j=start[i];j<=i;j++)
            tally[j]++;
    }
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>x;
        int result=find(x,0,n-1);
        if(result==-1)
            cout<<"No"<<endl;
        else
            cout<<"Yes "<<start[result]+1<<" "<<tally[start[result]]<<endl;
    }

}