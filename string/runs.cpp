/*洛谷 P6656 【模板】Runs
 *题目描述
 *定义一个字符串S里的一个run，指其内部一段两侧都不能扩展的周期子串，且周期至少完整出现两次。
 *严格地说，一个run是一个三元组(i,j,p)，满足p是S[i..j]的最小周期，j-i+1≥2p，且满足如下两个条件：
 *要么i=1，要么S[i-1]≠S[i-1+p]；
 *要么j=n，要么S[j+1]≠S[j+1-p]；
 *给定字符串S，求他的所有runs。
 */
#include <iostream>
using namespace std;
string s;
int find(int i,int p){
    int c=1;
    int j=i+p;
    while(j<s.size()){
        if(s[j]==s[i+(j-i)%p])
            ++j;
        else
            break;
        if((j-i)%p==0)
            ++c;
    }
    if(c<2)
        return 0;
    if(p==1)
        j=j-1;
    else
        j=i+c*p-1;
    if((i!=0&&s[i-1]==s[i-1+p])||(j!=s.size()-1&&s[j+1]==s[j+1-p]))
        return 0;
    else
        return j;
}
int main(){
    while(cin>>s){
        for(int i=0;i<s.size();i++)
            for(int p=1;p<=(s.size()-i)/2;p++){
                int j=find(i,p);
                if(j!=0)
                    cout<<i+1<<" "<<j+1<<" "<<p<<endl;
            }
    }
}