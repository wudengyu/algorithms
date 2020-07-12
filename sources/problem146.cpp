/*机智零崎不会没梗Ⅱ
*Huffman编码——贪心算法
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int alphabet[52];
int main(){
    int t;
    cin>>t;
    cin.get();
    while(t--){
        memset(alphabet,0,sizeof(alphabet));
        priority_queue<int,vector<int>,greater<int> > q;
        string s;
        cin>>s;
        int len=s.size();
        for(int i=0;i<len;i++){
            if(s[i]>='A'&&s[i]<='Z')
                alphabet[s[i]-'A']++;
            if(s[i]>='a'&&s[i]<='z')
                alphabet[s[i]-'a'+26]++;
        }
        while(!q.empty())
            q.pop();
        for(int i=0;i<52;i++)
            if(alphabet[i]>0)
                q.push(alphabet[i]);
        int ans=0;
        while(q.size()>1){
            int l=q.top();
            q.pop();
            int r=q.top();
            q.pop();
            ans+=(l+r);
            q.push(l+r);
        }
        cout<<ans<<endl;
    }
}
