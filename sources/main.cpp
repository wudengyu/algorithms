#include <iostream>
#include <complex>
using namespace std;
const double PI=acos(-1);
int main(){
    complex<double> a(cos(2*PI),sin(2*PI));
    cout<<a<<endl;
}