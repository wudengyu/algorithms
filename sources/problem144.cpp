/*出口胡萝卜
 *矩形填充问题
*/
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    int h[6];
    int used;
    while(true){
        for(int i=0;i<6;i++){
            if((cin>>h[i]).eof())
                return 0;
        }
        used=0;
        used+=h[5];//处理6×6
        for(int i=4;i>=3;i--){
            used+=h[i];
            h[4-i]-=h[i]*(6+(i+1))/(6-(i+1));
        }//处理5×5、4×4
        for(int i=2;i>=0;i--){
            if(h[i]>0){
                used+=h[i]/(36/((i+1)*(i+1)));
                h[i]%=36/((i+1)*(i+1));
                if(h[i]>0){
                    used++;
                    h[i]-=36/((i+1)*(i+1));
                }
            }
            if(i>0&&h[i]<0){
                if(i==2&&h[i]==-3){//剩于3×3等于3个时的特殊处理
                    h[i]+=3;
                    h[1]-=5;
                    h[0]-=7;
                }
                if(i==2&&h[i]==-2){//剩于3×3等于2个时的特殊处理
                    h[i]+=2;
                    h[1]-=3;
                    h[0]-=6;
                }
                while(h[i]<0){
                    h[i]++;
                    h[i-1]--;
                    h[0]-=2*i+1;
                }
            }
        }
        cout<<used<<endl;
    }
}