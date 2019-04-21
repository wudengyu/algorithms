#include <stdio.h>
#include <stdlib.h>
typedef struct vertex{
    int index;
    struct vertex* next;
}VERTEX;
void scaler_vertex(VERTEX **scaler,int offset,VERTEX* v){
    v->next=*(scaler+offset);
    *(scaler+offset)=v;
}
VERTEX *s[100000],a[100000];
int work[100000],pre[100000];
int find_pre(int x){
    if(pre[x]==x)
        return x;
    return pre[x]=find_pre(pre[x]);
}
int main(){
    int t,n;
    scanf("%d",&t);
    for(int x=0;x<t;x++){
        int max=0,temp=0,current_vertex=-1;
        VERTEX* temp_vertex=NULL;
        long long resonance=0;
        scanf("%d",&n);
        for(int i=0;i<100000;i++){
            s[i]=NULL;
            work[i]=0;
            pre[i]=i;
        }
        for(int i=0;i<n;i++){
            scanf("%d",&temp);
            a[i].index=i;
            a[i].next=NULL;
            scaler_vertex(s,temp,&a[i]);
            if(temp>max)
                max=temp;
        }
        for(int i=max;i>0;i--){
            int ti=i;
            while(s[ti]==NULL){
                ti+=i;
                if(ti>max)
                    break;
            }
            if(ti>max)
                continue;
            else
                current_vertex=s[ti]->index;
            for(int j=ti;j<=max;j+=i){
                temp_vertex=s[j];
                while(temp_vertex!=NULL){
                    if(find_pre(temp_vertex->index)!=find_pre(current_vertex)){
                        pre[temp_vertex->index]=find_pre(current_vertex);
                        resonance+=i;
                    }
                    temp_vertex=temp_vertex->next;
                }
            }
        }
        printf("%lld\n",resonance);
    }
}

