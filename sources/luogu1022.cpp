#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    char c,x;
    int a=0,b=0,num=0,op=1,eq=1;
    while((c=getchar())!=EOF){
        if(c>='0'&&c<='9')
            num=num*10+c-'0';
        else if(c>='a'&&c<='z'){
            x=c;
            a+=num==0?op*eq:op*eq*num;
            num=0;
        }else{
            b+=eq*op*num;
            op=1;
            num=0;
            if(c=='-')
                op=-1;
            if(c=='=')
                eq=-1;
        }
        if(c=='\n')
            break;
    }
    if(b==0)
        cout<<fixed<<setprecision(3)<<x<<"="<<0.000<<endl;
    else
        cout<<fixed<<setprecision(3)<<x<<"="<<-(float)b/a<<endl;
}