#include<iostream>
#include<cstring>
using namespace std;
class big_integer:public string{
    public:
    big_integer():string(){}
    big_integer(const string s):string(s){}
    big_integer(size_t length,char fill):string(length,fill){}
    big_integer(const char s[]):string(s){}
    big_integer(const big_integer &x):string(x.data()){}
    big_integer &operator*(const big_integer&);
    big_integer &operator=(unsigned long long);
    bool operator>(const big_integer&);
    big_integer &ltrim();
    big_integer substr(size_t,size_t);
};
big_integer &big_integer::operator*(const big_integer& multiplier){
    big_integer product(size()+multiplier.size(),'0');
    int carry;
    string::const_reverse_iterator i;
    string::reverse_iterator j;
    for(i=multiplier.rbegin(),j=product.rbegin();i!=multiplier.rend();i++,j++){
        carry=0;
        for(string::reverse_iterator k=rbegin(),l=j;k!=rend();k++,l++){
            *l+=(*k-'0')*(*i-'0')+carry-'0';
            carry=*l/10;
            *l=*l%10+'0';
            if(k==rend()&&carry!=0){
                *(l+1)+=carry;
            }
        }
    }
    product.ltrim();
    swap(product);
    return *this;
}
big_integer &big_integer::operator=(unsigned long long i){
    char temp;
    while(i){
        push_back(i%10+'0');
        i/=10;
    }
    for(auto i=begin(),j=end();i<j;i++,j--){
        temp=*i;
        *i=*j;
        *j=temp;
    }
    return *this;
}
big_integer &big_integer::ltrim(){
    int count=0;
    for(auto i=begin();i!=end();i++){
        if(*i==0||*i=='0')
            count++;
        else
            break;
    }
    if(count>0){
        for(int i=count;i<this->size();i++)
            at(i-count)=at(i);
        resize(size()-count);
    }
    return *this;  
}
bool big_integer::operator>(const big_integer &b){
    bool returnvalue=false;
    if(size()>b.size())
        return true;
    else if(size()<b.size())
        return false;
    else{
        string::iterator i;
        string::const_iterator j;
        for(i=begin(),j=b.begin();i!=end();i++,j++){
            if(*i>*j){
                returnvalue=true;
                break;
            }else if(*i<*j){
                returnvalue=false;
                break;
            }
        }
    }
    return returnvalue;
}
big_integer big_integer::substr(size_t begin,size_t end){
    return big_integer(string::substr(begin,end-begin+1));
}
int pos[8];
big_integer max_product=0ull;
big_integer product(const big_integer &question,int k){
    big_integer result=1ull;
    for(int i=1;i<=k+1;i++)
        result=result*question.substr(pos[i-1]+1,pos[i]);
    return result;
}
/*
void dfs(int depth,int k){
    unsigned long long temp;
    int original=pos[depth];//每次进入，都保存原始位置，返回时还原
    if(depth>1){
        dfs(depth-1,k);//本身不动，向下深搜
        for(int i=pos[depth]+1;i<pos[depth+1];i++){
            pos[depth]=i;//位置向后移
            temp=product(k);
            if(temp>max_product)
                max_product=temp;
            dfs(depth-1,k);//移动后再继续深搜
        }
    }else{
        for(int i=pos[depth]+1;i<pos[depth+1];i++){
            pos[depth]=i;//位置向后移
            temp=product(k);
            if(temp>max_product)
                max_product=temp;
        }
    }
    pos[depth]=original;
} 
*/
int main(){
    int n,k;
    big_integer question;
    cin>>n>>k>>question;
    for(int i=1;i<=k;i++)
        pos[i]=i;//乘号初始位置
    pos[0]=0;
    pos[k+1]=n;
    cout<<product(question,k)<<endl;
}