#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
struct site{
    double d,p;
};
bool cmp(site a,site b){
    return a.d<b.d;
}
int main(){
    int n;
    int current_site=0,next_site;//当前站点、下一站
    double c,pd,cost=0;//油箱容量、每升公里数、费用
    double current_distance=0,current_oil=0;
    double d0,p0;
    site s[8];
    cin>>d0>>c>>pd>>p0>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i].d>>s[i].p;
    }
    s[n+1].d=d0;
    s[n+1].p=0;
    s[0].d=0;
    s[0].p=p0;
    sort(s,s+n+1,cmp);
    while(current_site<(n+1)){
        next_site=current_site;
        double fear=current_distance+c*pd;
        if(fear<s[current_site+1].d){
            cout<<"No Solution"<<endl;
            return 0;
        }
        for(int i=current_site+1;i<n+2&&s[i].d<=fear;i++){
            if(s[i].p<=s[current_site].p){
                next_site=i;
                if((s[i].d-current_distance)/pd>current_oil){//不一定需要加油
                    cost+=((s[i].d-current_distance)/pd-current_oil)*s[current_site].p;
                    current_oil=0;//加油时，到下一站恰好用完
                }else{
                    current_oil-=(s[next_site].d-s[current_site].d)/pd;//不加油时，剩余的油量
                }
                current_distance=s[next_site].d;//更新距离到可到达站点
                break;
            }
        }
        if(next_site==current_site){
            cost+=(c-current_oil)*s[current_site].p;//加满
            current_distance=s[current_site+1].d;//更新距离到下一站
            current_oil=c-(current_distance-s[current_site].d)/pd;//计算剩余油量
            current_site++;
        }else{
            current_site=next_site;
        }
    }
    cout<<fixed<<setprecision(2)<<cost<<endl;
}