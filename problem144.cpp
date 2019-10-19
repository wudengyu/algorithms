/*出口胡萝卜
 *矩形填充问题
*/
#include <iostream>
using namespace std;
void swap(int &a,int &b){
    int tmp=a;
    a=b;
    b=tmp;
}
int fill(int p[],int length,int m,int n){
    cout<<"Begin Fill And m="<<m<<",n="<<n<<endl;
    for(int i=0;i<length;i++)
        cout<<p[i]<<' ';
    cout<<endl;
    int count=0;
    if(!m&&n)
        return 0;
    if(m<n)
        swap(m,n);
    for(int i=length-1;i>=0;i--){
        if(p[i]>0&&n>=i+1){
            count++;
            p[i]--;
            count+=fill(p,length,m,n-i-1);
            count+=fill(p,length,m-i-1,i+1);
            break;
        }
    }
    cout<<"Fill Over And Filled="<<count<<endl;
    for(int i=0;i<length;i++)
        cout<<p[i]<<' ';
    cout<<endl;
    return count;
}
int main(){
    int h[6];
    int leave,count;
    while(true){
        count=0;
        leave=0;
        for(int i=0;i<6;i++){
            if((cin>>h[i]).eof())
                return 0;
            leave+=h[i];
        }
        while(leave>0){
            leave-=fill(h,6,6,6);
            count++;
        }
        cout<<count<<endl;
    }
}