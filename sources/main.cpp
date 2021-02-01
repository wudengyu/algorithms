#include <iostream>
#include <complex>
using namespace std;
int a[100000],b[100000],c[100000];
const double PI=acos(-1);
int main(){
    complex<double> a(cos(2*PI),sin(2*PI));
    cout<<a<<endl;
}