#include<iostream>
#include<cstring>
#include<map>
using namespace std;
int main(){
    char secret[101],plain[101],question[101];
    int marked[26];
    char dict[26];
    memset(secret,0,sizeof(secret));
    memset(plain,0,sizeof(plain));
    memset(question,0,sizeof(question));
    memset(marked,0,sizeof(marked));
    memset(dict,0,sizeof(dict));
    cin>>secret>>plain>>question;
    for(int i=0;i<strlen(secret);i++){
        if(marked[plain[i]-'A']==0){
		   dict[plain[i]-'A']=secret[i];
           marked[plain[i]-'A']=1;
	    }
		if(marked[plain[i]-'A']!=0){
			if(dict[plain[i]-'A']!=secret[i]){
				cout<<"Failed"<<endl;
                return 0;
			}
		}
    }
    for(int i=0;i<26;i++){
        if(marked[i]==0){
            cout<<"Failed"<<endl;
            return 0;
        }
    }
    for(int i=0;i<strlen(question);i++){
		for(int j=0;j<26;j++){
			if(dict[j]==question[i])
				cout<<(char)('A'+j);
		}
    }
}