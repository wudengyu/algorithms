#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,m,i=0,j=0,max_win=0;
    char c,xg[100000],yj[100000];
    scanf("%d%d\n",&n,&m);
    while((c=getchar())!='\n'){
        xg[i++]=c;
    }
    while((c=getchar())!='\n'){
        switch(c){
            case 'R':
                yj[j++]='S';
                break;
            case 'S':
                yj[j++]='P';
                break;
            case 'P':
                yj[j++]='R';
                break;
        }
    }
    for(int i=0;i<n;i++){
        int temp_win=0;
        for(int j=0;j<m&&i+j<n;j++)
            if(xg[i+j]==yj[j])
                temp_win++;
        if(temp_win>max_win)
            max_win=temp_win;
    }
    printf("%d\n",max_win);
}