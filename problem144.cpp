/*出口胡萝卜
 *矩形填充问题
*/
#include <iostream>
#include <cstring>
using namespace std;
struct coordinates{
    int x;
    int y;
};
enum{
    margin_top=0x1,
    margin_right=0x2,
    margin_bottom=0x4,
    margin_left=0x8,
    impossible=0x10,
    first=0x20
};
class Box{
    private:
    int space[6][6];
    int size;
    int count;
    public:
    Box();
    void reset();
    void fill(int x,int y,int side);
    int explore(int x,int y,int side);
    bool lay(int side);
    int lay(int shape[],int length,int total);
};
Box::Box(){
    size=6;
}
void Box::reset(){
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            space[i][j]=0;
    count++;
}
void Box::fill(int x,int y,int side){
    for(int i=x;i<x+side;i++)
        for(int j=y;j<y+side;j++)
            space[i][j]=side;
}
int Box::explore(int x,int y,int side){
    int status=0;
    if(x+side>=size||y+side>=size){
        status|=impossible;
        return status;
    }
    if(x==0&&y==0)
        status|=first;
    for(int i=x;i<x+side;i++){
        for(int j=y;j<y+side;j++){
            if(space[i][j]){
                status|=impossible;
                break;
            }
            if(i==x&&(i==0||space[i-1][j]))
                status|=margin_top;//上边不为空
            if(i==x+side&&(i==size||space[i+1][j]))
                status|=margin_bottom;//下边不为空
            if(j==y&&(j==0||space[i][j-1]))
                status|=margin_left;//左边不为空
            if(j==y+side&&(j==size||space[i][j+1]))
                status|=margin_right;//右边不为空
        }
        if(status&impossible)
            break;
    }
    return status;
}
bool Box::lay(int side){
    int last_x,last_y,last_status=impossible;
    int status;
    int border;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(!space[i][j]){
                status=explore(i,j,side);
                if(status&impossible)
                    continue;
                last_x=i;
                last_y=j;
                last_status=status;
                border=0;
                for(int k=1;k<0x10;k<<=1){
                    if(status&k)
                        border++;
                }
                if(status&first||border>=3){
                    fill(i,j,side);
                    return true;
                }
            }
        }
    }
    if(!(last_status&impossible)){
        fill(last_x,last_y,side);
        return true;
    }
    return false;
}
int Box::lay(int shape[],int length,int total){
    this->count=0;
    while(total>0){
        this->reset();
        int finger=length;
        while(finger>=0){
            if(shape[finger]&&lay(finger+1)){
                shape[finger]--;
                total--;
            }else
                finger--;
        }
    }
    return this->count;
}
int main(){
    int h[6],total;
    Box b=Box();
    while(true){
        total=0;
        for(int i=0;i<6;i++){
            if((cin>>h[i]).eof())
                return 0;
            total+=h[i];
        }
        cout<<b.lay(h,6,total)<<endl;
    }
}