#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,d,min,max,*p;
    scanf("%d",&n);
    if(n==1||n==2){
        printf("Yes\n");
        return 0;
    }
    p=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",p+i);
        if(i==0){
            min=p[i];
            max=p[i];
        }else{
            if(p[i]<min)
                min=p[i];
            if(p[i]>max)
                max=p[i];
        }
    }
    if((max-min)%(n-1)){
        printf("NO\n");
        return 1;
    }else{
        d=(max-min)/(n-1);
        for(int i=0;i<n;i++){
            if((p[i]-min)%d!=0||(p[i]-min)/d>=n){
                printf("NOn");
                return 1;
            }
        }
        printf("Yes\n");
    }
    return 0;
}