#include<iostream>
using namespace std;
int main(){
    int n,orderinrow;
    cin>>n;
    int row=1;
    while(row+row*(row-1)/2<n)row++;
    orderinrow=n-((row-1)+(row-1)*(row-2)/2);
    if(row%2==0)
        cout<<orderinrow<<"/"<<row+1-orderinrow<<endl;
    else
        cout<<row+1-orderinrow<<"/"<<orderinrow<<endl;
}