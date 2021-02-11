#include<iostream>
using namespace std;
struct rug{
    int a;
    int b;
    int g;
    int k;
};
int find(const rug (&carpet)[10000],int length,int x,int y){
    for(int i=length-1;i>=0;i--){
        if(carpet->a<=x&&carpet->a+carpet->g>=x&&carpet->b<=y&&carpet->b+carpet->g>=y)
            return i+1;
    }
    return -1;
}
int main(){
    rug carpet[10000];
    int n,x,y;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>carpet[i].a>>carpet[i].b>>carpet[i].g>>carpet[i].k;
    }
    cin>>x>>y;
    cout<<find(carpet,n,x,y)<<endl;
}