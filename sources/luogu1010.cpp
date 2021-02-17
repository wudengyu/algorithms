#include<iostream>
using namespace std;
void polynomial(int x){
    unsigned int marked=1<<31;
    int exponential=31;
    while(marked){
        if(x==0)break;
        if(x&marked){
            switch(exponential){
                case 2:
                    cout<<"2(2)";
                    break;
                case 1:
                    cout<<"2";
                    break;
                case 0:
                    cout<<"2(0)";
                    break;
                default:
                    cout<<"2(";
                    polynomial(exponential);
                    cout<<")";
                    break;
            }
            x&=~marked;
            if(x!=0)
                cout<<"+";
        }
        marked>>=1;
        exponential--;
    }
}
int main(){
    int n;
    cin>>n;
    polynomial(n);
    cout<<endl;
}