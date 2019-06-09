/*Bella 姐姐发辣条*/
#include <stdio.h>
int main(){
    int t,n,a[100],b[100];
    int last,sum;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        last=0;
        sum=0;
        for(int i=0;i<n;i++){
            if(last+b[i]>a[i]){
                last+=b[i];
            }else{
                sum+=i*(a[i]-b[i]-last);//给当前小朋友多发了几根，就需要给前面的小朋友都补上，这样才能满足第二个条件『恰好』比前一个小朋友多b[i]根。
                last=a[i];
            }
            sum+=last;
        }
        printf("%d\n",sum);
    }
}