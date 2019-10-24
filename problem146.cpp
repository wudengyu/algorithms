/*机智零崎不会没梗Ⅱ
*Huffman编码——贪心算法
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Node{
    int freq;
    Node* left;
    Node* right;
    friend bool operator<(Node a,Node b){
        return a.freq>b.freq;
    }
};
int length(Node* t,int dept){
    int sum=0;
    if(t->left==nullptr&&t->right==nullptr){
        return t->freq*dept;
    }
    if(t->left!=nullptr){
        sum+=length(t->left,dept+1);
    }
    if(t->right!=nullptr){
        sum+=length(t->right,dept+1);
    }
    return sum;
}
int alphabet[52];
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(alphabet,0,sizeof(alphabet));
        char c;
        Node tmp,*root;
        priority_queue<Node> q;
        cin.ignore('\n');
        while((c=cin.get())!='\n'){
            if(c>='A'&&c<='Z')
                alphabet[c-'A']++;
            if(c>='a'&&c<='z')
                alphabet[c-'a'+26]++;
        }
        for(int i=0;i<52;i++){
            if(alphabet[i]>0){
                tmp.freq=alphabet[i];
                tmp.left=nullptr;
                tmp.right=nullptr;
                q.push(tmp);
                if(i<26)
                    cout<<(char)(i+'A')<<':'<<alphabet[i]<<endl;
                else
                {
                    cout<<(char)(i-26+'a')<<':'<<alphabet[i]<<endl;
                }
                
            }
        }
        while(q.size()>1){
            Node* l=new Node;
            Node* r=new Node;
            *l=q.top();
            q.pop();
            *r=q.top();
            q.pop();
            tmp.left=l;
            tmp.right=r;
            tmp.freq=l->freq+r->freq;
            q.push(tmp);
        }
        root=new Node();
        *root=q.top();
        q.pop();
        cout<<length(root,0)<<endl;
    }
}
