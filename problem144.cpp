/*出口胡萝卜
 *矩形填充问题
*/
#include <iostream>
#include <cstring>
using namespace std;
int baskets[8][6]={{0,0,0,0,0,1},{11,0,0,0,1,0},{0,5,0,1,0},{0,0,4,0},
    {6,3,2,0},{7,5,1,0},{0,9,0},{36,0}};
int main(){
    int h[6];
    int use[8];
    int sum=0;
    while(true){
        for(int i=0;i<6;i++){
            if((cin>>h[i]).eof())
                return 0;
        }
        memset(use,0,sizeof(use));
        use[0]=h[5];
        use[1]=h[4];
        use[2]=h[3];
        use[3]=h[2]/4;
        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++)
                h[j]-=baskets[i][j]*use[i];
        }
        if(h[1]<0){
            h[0]-=-h[1]*4;
            h[1]=0;
        }
        if(h[2]==3){
            use[3]++;
            h[2]=0;
            if(h[1]>0){
                h[1]-=1;
                h[0]-=3;
            }else
                h[0]-=9;
        }else if(h[2]==2){
            use[4]++;
            h[2]=0;
            if(h[1]>=3){
                h[1]-=3;
                h[0]-=6;
            }else{
                h[0]=h[0]-6-(3-h[1])*4;
                h[1]=0;
            }
        }else if(h[2]==1){
            use[5]++;
            h[2]=0;
            if(h[1]>=5){
                h[1]-=5;
                h[0]-=7;
            }else{
                h[0]=h[0]-7-(5-h[1])*4;
                h[1]=0;
            }
        }
        if(h[1]>0){
            use[6]=h[1]/9;
            h[1]%=9;
            if(h[1]>0){
                use[6]++;
                h[0]-=36-4*h[1];
                h[1]=0;
            }
        }
        if(h[0]>0){
            use[7]=h[0]/36;
            h[0]%=36;
            if(h[0]>0)
                use[7]++;
        }
        sum=0;
        for(int i=0;i<8;i++){
            sum+=use[i];
            cout<<use[i]<<' ';
        }
        cout<<endl;
        cout<<sum<<endl;
        }
}