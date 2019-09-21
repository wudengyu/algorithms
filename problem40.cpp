#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const float max_distince=1.5e9;
struct Point{
    int x;
    int y;
    int type;
};
inline bool compx(const Point& a,const Point& b){
    return a.x<b.x;
}
inline bool compy(const Point& a,const Point& b){
    return a.y<b.y;
}
inline float min(float a,float b){
    return a<b?a:b;
}
float distince(const Point& a,const Point& b){
    if(a.type==b.type)
        return max_distince;//如果两个点是同一类型，则返回最大距离；
    else
        return sqrt((float)(b.x-a.x)*(b.x-a.x)+(float)(b.y-a.y)*(b.y-a.y));
}
float solve(Point* p,int m,int n){
    if(m==n) return max_distince;//如果待处理区间只有一个点，那么返回最大距离；
    if(n=m+1) return distince(p[m],p[n]);//如果待处理区间有两个点，那么最小距离就是这两点之间的距离；
    /*如果不是前面两种情况，即待处理区间有三个以上的点，则分而治之，并且取分治两边中最小的距离作为暂时得到的最小距离。
     *实际上，三个点时已经不必再分，可以直接遍历找最小距离了。因为三个点只能分成一个和两个，一个的话距离就是最大值，
     *这样后面归并时仍然要把所有的点考虑进来进行遍历。如果三个点直接遍历，那就不用考虑只有一个点的情况，因为不会出现
     *只有一个点的情况了，三个点依然分治，只是代码看上去短一点。
    */
    float min_distince=min(solve(p,m,m+(n-m)/2),solve(p,m+(n-m)/2+1,n));//如果不是前面两种情况，即有3个点以上，那


    
    int d=n-m;
}
int main(){
    int k,n;
    Point* p;
    cin>>k;
    while(k--){
        cin>>n;
        p=new Point[2*n];
        for(int i=0;i<n;i++){
            cin>>p[i].x>>p[i].y;
            p[i].type=0;
        }
        for(int i=n;i<2*n;i++){
            cin>>p[i].x>>p[i].y;
            p[i].type=1;
        }
        /*
        sort(p,p+n,compx);
        for(int i=0;i<n;i++)
            cout<<'('<<p[i].x<<','<<p[i].y<<')'<<' ';
        */
       cout<<distince(p[0],p[1]);

    }
    
}