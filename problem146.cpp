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
int alphabet[52];
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(alphabet,0,sizeof(alphabet));
        char c;
        Node tmp,*root;
        priority_queue<Node> q;
        cout<<q.size();   
        cin.ignore();
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
            }
        }
        while(q.size()>1){
            Node* r=new Node;
            Node* l=new Node;
            Node* r=new Node;
            *l=q.top();
            q.pop();
            *r=q.top();
            q.pop();
            r->left=l;
            r->right=r;
            r->freq=l->freq+r->freq;
            q.push(*r);
            delete r;
        }
        root=new Node;
        *root=q.top();
        q.pop();
    }
}
