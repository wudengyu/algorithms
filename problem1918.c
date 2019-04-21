#include <stdio.h>
int main(){
    int t,n,a[100],b[100];
    int last,sum,plus=0;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        last=a[0];
        sum=a[0];
        for(int i=1;i<n;i++){
            if(last+b[i]>a[i]){
                last+=last+b[i];
                sum=sum+last;
            }else{
                plus=a[i]-b[i]-last;
                last=a[i];
                sum=sum+last+i*plus;
            }
        }
        printf("%d\n",sum);
    }
}