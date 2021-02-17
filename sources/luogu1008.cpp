#include<iostream>
using namespace std;
bool test(int a[]){
    int s[10]={1,0,0,0,0,0,0,0,0,0};
    int temp=0;
    a[1]=a[0]*2;
    a[2]=a[0]*3;
    for(int i=0;i<3;i++){
        temp=a[i];
        while(temp){
            if(s[temp%10])
                return false;
            s[temp%10]++;
            temp/=10;
        }
    }
    return true;
}
int main(){
    int a[3];
    for(a[0]=123;a[0]<=329;a[0]++){
        if(test(a))
            cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
    }
}