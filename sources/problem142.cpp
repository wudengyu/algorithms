/*大家一起数钢镚*/
#include <iostream>
using namespace std;
int main(){
    int a[6],b[6]={1,5,10,50,100,500},m;
    int count;
    while(true){
        for(int i=0;i<6;i++)
            if((cin>>a[i]).eof())
                return 0;
        cin>>m;
        count=0;
        for(int i=5;i>=0;i--){
            if(a[i]*b[i]>=m){
                count+=m/b[i];
                m%=b[i];
            }else{
                count+=a[i];
                m-=a[i]*b[i];
            }
        }
        cout<<count<<endl;
    }
}