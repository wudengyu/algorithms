#include <stdio.h>
int extend_gcd(int a,int b,int *x,int *y){
    if(b==0){
        *x=1;
        *y=0;
        return a;
    }else{
        int r=extend_gcd(b,a%b,x,y);
        int t=*x ;
        *x=*y ;
        *y=t-a/b**y ;
        return r ;
    }
}
int main(){
    printf("%d\n",gcd(1239,369));
}