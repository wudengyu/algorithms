/*禁忌的共鸣*/
#include <stdio.h>
#include <stdlib.h>
typedef struct vertex{
    int index;
    struct vertex* next;
}VERTEX;//点，因为同一能力值的点可能有多个，所以需要采用链式结构存储
/*
把点加到链表里
*/
void scaler_vertex(VERTEX **scaler,int offset,VERTEX* v){
    v->next=*(scaler+offset);
    *(scaler+offset)=v;
}
VERTEX *s[100000],a[100000];//s是指向点链的数组，a是保存原始值的数组，定义数组a之后，就不再动态申请内存，因为malloc很耗时。
int work[100000],pre[100000];//work是运算中保存临时数据的，pre是并查集，每个位置的内容是其父节点位置。
/*递归查找一个节点所在树的根节点，根节点的标志就是指向自身，由于是用于并查集，所以如果有父节点，就修改自身指向父节点，以缩小树的层数。*/
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
        //初始化
        for(int i=0;i<100000;i++){
            s[i]=NULL;
            work[i]=0;
            pre[i]=i;
        }
        for(int i=0;i<n;i++){
            scanf("%d",&temp);
            a[i].index=i;
            a[i].next=NULL;//初始化点
            scaler_vertex(s,temp,&a[i]);//将点加入到链表数组，数组的索引是点的值，同一值的点组成链；
            if(temp>max)//顺便获取一个最大值，后面从最大到最小倒序遍历，从n开始也行，但是如果最大值比n小得多可以快一些
                max=temp;
        }
         for(int i=max;i>0;i--){//倒序查找
            int count_point=0;
            VERTEX *temp_vertex=NULL;
            for(int j=i;j<=max;j+=i){
                temp_vertex=s[j];
                //当前数（i的倍数）有内容。即：把i倍数取出来放到临时空间（work数组），已经取出的数字计数值是count_point
                while(temp_vertex!=NULL){
                    work[count_point]=temp_vertex->index;
                    temp_vertex=temp_vertex->next;
                    count_point++;
                }
            }
            /*检查work中的数，如果有两个以上，则检查是否同一并查集，如果不是同一并查集则加入生成树，同时增加树的总花费。*/
            for(int j=0;j<count_point;j++)
                if(find_pre(pre[j])!=find_pre(pre[0])){
                    pre[find_pre(work[j])]=find_pre(pre[0]);
                    resonance+=i;
                }
        }
        printf("%lld\n",resonance);
    }
}