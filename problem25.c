#include <stdio.h>
int prime(int x){
    if(x==1)
        return 0;
    for(int i=2;i*i<=x;i++)
        if(x%i==0)
            return 0;
    return 1;
}
int main(){
    int t,x;
    scanf("%d",&t);
    for(int i=0;i<t;i++){
        scanf("%d",&x);
        if(prime(x))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
