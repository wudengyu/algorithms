#include<iostream>
using namespace std;
struct node{
    int left;
    int right;
    int d;
}original[31];
long long create(int root);
void preorder(node tree[],int node){
    if(tree[node].left!=0)
        preorder(tree,tree[node].left);
    else
        cout<<node<<" ";
    if(tree[node].right!=0)
        preorder(tree,tree[node].right);
}
int main(){
    int n,root;
    long long bonus=0;
    node ans[31];
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>original[i].d;
    for(int i=1;i<=n;i++){
        long long temp;
        if((temp=create(i))>bonus){
            bonus=temp;
            root=i;
            for(int j=1;j<=n;j++)
                ans[j]=original[j];
        }
    }
    cout<<bonus;
    preorder(ans,root);
}
