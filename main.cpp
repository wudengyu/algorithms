#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
int main(){
    string a="ABCDE";
    string b="BCEFAB";
    cout<<"Hello World!"<<endl;
    cout<<typeid(a[1]).name()<<a.max_size()<<endl;
    cout<<(a[1]==b[0])<<endl;
    cout<<(-2+100)%100<<endl;
    cout<<(-2+200)%100<<endl;
    cout<<dec<<((unsigned)(-1)>>1)<<endl;

}