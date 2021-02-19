#include<iostream>
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int>> pq;
int main(){
    int n,temp,ans=0,sum;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>temp;
        pq.push(temp);
    }
    while(pq.size()>=2){
        sum=pq.top();
        pq.pop();
        sum+=pq.top();
        pq.pop();
        ans+=sum;
        pq.push(sum);

    }
    cout<<ans<<endl;
}