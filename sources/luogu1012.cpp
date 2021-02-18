#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
bool compare(char *p,char *q){
    char *p_begin=p,*q_begin=q;
    char *p_end,*q_end;
    while(*p)p++;
    while(*q)q++;
    p_end=p;
    q_end=q;
    while((p!=p_begin||q!=q_begin)&&(p!=q_begin||q!=p_begin)){
        p--;
        q--;
        if(*p>*q){
            return true;
        }
        if(*p<*q){
            return false;
        }
        if(p==p_begin&&q!=q_begin)
                p=q_end;
        if(q==q_begin&&p!=p_begin)
                q=p_end;
    }
    return true;
}
void print(char *s){
    char *begin=s;
    while(*s)s++;
    while(s--!=begin){
        cout<<*s;
    }
}
int main(){
    int n;
    cin>>n;
    char s[n][10];
    memset(s,0,sizeof(char)*n*10);
    char *p[n];
    for(int i=0;i<n;i++){
        int temp,pos=0;
        cin>>temp;
        do{
            s[i][pos]=temp%10+'0';
            temp/=10;
            pos++;
        }while(temp);
        p[i]=s[i];
    }
    sort(p,p+n,compare);
    for(int i=0;i<n;i++){
        print(p[i]);
    }
    cout<<endl;
}