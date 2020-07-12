#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n,a[10000];
    while(!(cin>>n).eof()){
        long long ans=0;
        for(int i=0;i<n;i++)
            cin>>a[i];
        sort(a,a+n);
        for(int i=0;i<n;i++)
            ans+=(n-i-1)*a[i];
        cout<<ans<<endl;
    }
}