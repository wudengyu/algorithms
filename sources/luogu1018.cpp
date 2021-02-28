#include<iostream>
#include<cstring>
using namespace std;
class big_integer:public string{
    public:
    big_integer():string(){}
    big_integer(int);
    big_integer(const string s):string(s){}
    big_integer(size_t length,char fill):string(length,fill){}
    big_integer(const char *s):string(s){}
    big_integer(const big_integer &x):string(x.data()){}
    big_integer operator*(const big_integer&);
    bool operator>(const big_integer&);
    big_integer &ltrim();
    big_integer substr(size_t,size_t);
};
big_integer::big_integer(int i):string(){
    char temp;
    while(i){
        push_back(i%10+'0');
        i/=10;
    }
    for(auto i=begin(),j=end()-1;i<j;i++,j--){
        temp=*i;
        *i=*j;
        *j=temp;
    }
}
big_integer big_integer::operator*(const big_integer& multiplier){
    big_integer product(size()+multiplier.size(),'0');
    int carry;
    string::const_reverse_iterator i;
    string::reverse_iterator j;
    for(i=multiplier.rbegin(),j=product.rbegin();i!=multiplier.rend();i++,j++){
        carry=0;
        for(string::reverse_iterator k=rbegin(),l=j;;k++,l++){
            if(k==rend()){
                if(carry!=0)
                    *l+=carry;
                break;
            }
            *l+=(*k-'0')*(*i-'0')+carry-'0';
            carry=*l/10;
            *l=*l%10+'0';
        }
    }
    return product.ltrim();
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
int n,k;
big_integer f[41][41];
big_integer max_product=0;
void dfs(int num,big_integer product,int pos){
    big_integer temp;
    if(num==k){
        temp=product*f[pos+1][n];
        if(temp>max_product)
            max_product=temp;
    }else{
        for(int i=pos+1;i<=n-k+num;i++){
            dfs(num+1,product*f[pos+1][i],i);
        }
    }
}
int main(){
    big_integer question;
    cin>>n>>k>>question;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)
            f[i][j]=question.substr(i-1,j-1);
    }
    dfs(0,1,0);
    cout<<max_product<<endl;
}