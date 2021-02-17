#include<iostream>
using namespace std;
class bigint{
private:
    int b[100];
public:
    bigint(){
        for(int i=0;i<100;i++)
            b[i]=0;
    };
    bigint(const bigint &a){
        for(int i=0;i<100;i++)
            b[i]=a.b[i];
    };
    bigint(int a):bigint(){
        int i=0,temp=a;
        while(temp){
            b[i++]=temp%10;
            temp/=10;
        }
    }
    bigint &operator+(const bigint &a){
        int carry=0;
        for(int i=0;i<100;i++){
            b[i]+=a.b[i]+carry;
            carry=b[i]/10;
            b[i]=b[i]%10;
        }
        return *this;
    };
    bigint &operator*(int a){
        bigint result;
        int product,pos,carry,temp;
        for(int i=0;i<100;i++){
            product=b[i]*a;
            pos=i;
            carry=0;
            while(product||carry){
                result.b[pos]+=product%10+carry;
                carry=result.b[pos]/10;
                result.b[pos]%=10;
                product/=10;
                pos++;
            }
        }
        for(int i=0;i<100;i++)
            b[i]=result.b[i];
        return *this;
    };
    void output(){
        int i=99;
        while(b[i]==0)i--;
        while(i>0)
            cout<<b[i--];
        cout<<b[0];
    }
};
int main(){
    bigint sum=0,a=1;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        sum+a*i;
    }
    sum.output();
    cout<<endl;
    return 0;
}