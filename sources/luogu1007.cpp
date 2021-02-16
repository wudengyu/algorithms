#include<iostream>
using namespace std;
int main(){
    int bridge[5001];
    int l,n;
    int temp;
    int min_t=0,max_t=0;
    cin>>l>>n;
    for(int i=1;i<=l;i++)
        bridge[i]=0;
    for(int i=1;i<=n;i++){
        cin>>temp;
        bridge[temp]=1;
    }
    for(int i=1;i<=l;i++){
        if(bridge[i]!=0){
            if((temp=min(i,l+1-i))>min_t)
                min_t=temp;
            if((temp=max(i,l+1-i))>max_t)
                max_t=temp;
        }
    }
    cout<<min_t<<" "<<max_t<<endl;
}