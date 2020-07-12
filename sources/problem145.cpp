/*忙碌的Nova君
 *活动选择问题——贪心算法
*/
#include <iostream>
#include <algorithm>
using namespace std;
struct Activity{
    int s;
    int f;
}a[100000];
bool comp(Activity a,const Activity b){
    return a.f<b.f;
}
int main(){
    int n;
    while(!(cin>>n).eof()){
        int l=1,k=0;
        for(int i=0;i<n;i++)
            cin>>a[i].s>>a[i].f;
        sort(a,a+n,comp);
        for(int i=1;i<n;i++){
            if(a[i].s>a[k].f){
                l++;
                k=i;
            }
        }
        cout<<l<<endl;
    }
}