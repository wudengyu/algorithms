#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    int id;
    struct vertex* next;
}Vertex;
int max_heap[100001];//堆，用于实现优先队列
int heap_size=0;
void enqueue(int id){
    max_heap[++heap_size]=id;
    int p=heap_size;
    while(max_heap[p/2]<max_heap[p]&&p>1){
        int temp=max_heap[p/2];
        max_heap[p/2]=max_heap[p];
        max_heap[p]=temp;
        p/=2;
    }
}
int dequeue(void){
    int returnvalue=max_heap[1];
    max_heap[1]=max_heap[heap_size--];
    int p=1;
    while(2*p<=heap_size){
        int q=2*p;
        if(q<heap_size&&max_heap[q+1]>max_heap[q]) q++;
        if(max_heap[p]>max_heap[q]) break;
        int temp=max_heap[p];
        max_heap[p]=max_heap[q];
        max_heap[q]=temp;
        p=q;
    }
    return returnvalue;
}
int main(){
    int n,m;
    Vertex graph[100001];
    int indere[100001];//记录每个顶点的入度
    int ans[100001],tail=0;//记录结果，不过是倒序的,tail是结果队列的队尾；
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        graph[i].id=i;
        graph[i].next=NULL;
        indere[i]=0;
    }
    while(m--){
        int x,y;
        Vertex * new;
        scanf("%d%d",&x,&y);
        new=(Vertex *)malloc(sizeof(Vertex));
        new->id=x;
        new->next=graph[y].next;
        graph[y].next=new;
        indere[x]++;
    }
    //初始化队列，后面一边出队一边入队直到队列空。如果不初始化，则后面每处理一个顶点，不但要处理新产生的入度为0的顶点，还要处理以前没处理过的顶点。
    for(int i=1;i<=n;i++){
        if(indere[i]==0)
            enqueue(i);
    }
    while(heap_size>0){
        ans[++tail]=dequeue();
        while(graph[ans[tail]].next!=NULL){
            Vertex * temp=graph[ans[tail]].next;
            graph[ans[tail]].next=temp->next;
            if(--indere[temp->id]==0)
                enqueue(temp->id);
            free(temp);
        }
    }
    for(int i=tail;i>0;i--){
        printf("%d ",ans[i]);
    }
    return 0;
}