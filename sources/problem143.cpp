/*机智零崎不会没梗Ⅰ
 *看似背包，实际算不上，因为不需要DP。
 *因为数据范围大，用分数比较大小超出INT范围，只能采用浮点比较，单精度不够，得采用double。
*/
#include <iostream>
using namespace std;
int w[10005],v[10005];//w重量，v价值
int ind[10005];
bool compare(int x,int y){
    if((double)v[x]/w[x]>(double)v[y]/w[y])
        return true;
    else 
        return false;    
}
void max_heapify(int a[],int length,int i)
{
    int l=2*i,r=2*i+1,max,temp;
    if(l<=length && compare(a[l],a[i]))
        max = l;
    else
        max =i;
    if(r<=length && compare(a[r],a[max]))
        max = r;
    if(max != i)
    {
        temp=a[i];
        a[i]=a[max];
        a[max]=temp;
        max_heapify(a,length,max);
    }
}
void build_max_heap(int a[],int length){
    for(int i=length/2; i>=1; i--)
        max_heapify(a,length,i);
}
int main(){
    int g,k,n;//g背包承重，k物品数量，n价值期望
    while(!(cin>>g>>k>>n).eof()){
        for(int i=1;i<=k;i++){
            cin>>w[i]>>v[i];
            ind[i]=i;
        }
        build_max_heap(ind,k);
        int effect=0;
        double value=0;
        while(g>0&&effect++<k){
            if(w[ind[1]]>=g){
                value+=g*(double)v[ind[1]]/w[ind[1]];
                g=0;
            }else{
                value+=v[ind[1]];
                g-=w[ind[1]];
            }
            ind[1]=ind[k-effect+1];
            max_heapify(ind,k-effect,1);
        }
        cout.setf(ios_base::fixed);
        cout.precision(3);
        if(n<=value)
            cout<<"summon!"<<endl;
        else
            cout<<n-value<<endl;
    }
}