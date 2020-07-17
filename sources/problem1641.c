#include <stdio.h>
int a[200000],p[200000];
int main(){
    int n,ai,pi,tail=-1;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&ai,&pi);
        int s=tail++;
        while(s>0&&(a[s]>ai||a[s]==ai&&p[s]>pi))
        if(tail==-1){
            tail=0;
            a[tail]=ai;
            p[tail]=pi;
            continue;
        }
        int s=0;
        while(a[s]<ai&&s<=tail)
            s++;
        if(s>tail){
            tail++;
            a[tail]=ai;
            p[tail]=pi;
        }else if(a[s]==ai&&pi<p[s]){
            p[s]=pi;
        }
    }
}