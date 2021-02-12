#include<iostream>
using namespace std;
int main(){
    int n,x,y;
    int rug[10000][4];
    int ans=-1;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            cin>>rug[i][j];
        }
        rug[i][2]+=rug[i][0];
        rug[i][3]+=rug[i][1];
    }
    cin>>x>>y;
    for(int i=0;i<n;i++){
        if(x>=rug[i][0]&&x<=rug[i][2]&&y>=rug[i][1]&&y<=rug[i][3])
            ans=i+1;
    }
    cout<<ans<<endl;
}