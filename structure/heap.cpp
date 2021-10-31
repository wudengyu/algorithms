/*洛谷P3378 【模板】堆
 *题目描述
 *给定一个数列，初始为空，请支持下面三种操作：
 *给定一个整数x，请将x加入到数列中。
 *输出数列中最小的数。
 *删除数列中最小的数（如果有多个数最小，只删除1个）。
 *输入格式
 *第一行是一个整数，表示操作的次数n。
 *接下来n行，每行表示一次操作。每行首先有一个整数op表示操作类型。
 *若op=1，则后面有一个整数x，表示要将x加入数列。
 *若op=2，则表示要求输出数列中的最小数。
 *若op=3，则表示删除数列中的最小数。如果有多个数最小，只删除1个。
 *输出格式
 *对于每个操作2，输出一行一个整数表示答案。
*/
#include <iostream>
using namespace std;
const int N=10;
int heap[N+1],tail=0;
void swim(){
    int pos=tail;
    while(pos>1&&heap[pos/2]>heap[pos]){
        int tmp=heap[pos/2];
        heap[pos/2]=heap[pos];
        heap[pos]=tmp;
        pos/=2;
    }
}
void sink(){
    int pos=1;
    while((pos*2<=tail&&heap[pos]>heap[pos*2])||(pos*2+1<=tail&&heap[pos]>heap[pos*2+1])){
        int tmp=heap[pos];
        pos*=2;
        if(pos+1<=tail&&heap[pos]>heap[pos+1])
            ++pos;
        heap[pos/2]=heap[pos];
        heap[pos]=tmp;
    }
}
int main(){
    int n,op,x;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>op;
        switch(op){
            case 1:
                cin>>x;
                heap[++tail]=x;
                swim();
                break;
            case 2:
                cout<<heap[1]<<endl;
                break;
            case 3:
                heap[1]=heap[tail--];
                sink();
                break;
        }
    }
}
