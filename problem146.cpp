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
char buf[2001];
int alphabet[52];
int main(){
    int t;
    cin>>t;
    cin.get();
    while(t--){
        memset(alphabet,0,sizeof(alphabet));
        memset(buf,0,sizeof(buf));
        Node tmp,*root;
        priority_queue<Node> q;
        cin.getline(buf,2001,'\n');
        int len=strlen(buf);
        for(int i=0;i<len;i++){
            if(buf[i]>='A'&&buf[i]<='Z')
                alphabet[buf[i]-'A']++;
            if(buf[i]>='a'&&buf[i]<='z')
                alphabet[buf[i]-'a'+26]++;
        }
        for(int i=0;i<52;i++){
            if(alphabet[i]>0){
                tmp.freq=alphabet[i];
                tmp.left=nullptr;
                tmp.right=nullptr;
                q.push(tmp);
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
