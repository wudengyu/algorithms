#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
using namespace std;
int main(){
    cout<<"Hello World!"<<endl;
    int a=((unsigned)-1)>>1,b=1;
    cout.setf(ios_base::fixed);
    cout.precision(6);
    cout<<a/b<<endl;
    cout<<(float)a/b<<endl;
}