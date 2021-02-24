#include<iostream>
using namespace std;
struct node{
    int left;
    int right;
    int d;
}original[31];
void preorder(node tree[],int node){
    if(node==0)
        return;
    cout<<node;
    if(tree,tree[node].left!=0){
        cout<<" ";
        preorder(tree,tree[node].left);
    }
    if(tree,tree[node].right!=0){
        cout<<" ";
        preorder(tree,tree[node].right);
    }   
}
unsigned int create(int left,int root,int right){
    unsigned int l_score=0,r_score=0,l_max=0,r_max=0;
    int l_root,r_root;
    node temp[31];
    if(left==root){
        original[root].left=0;
        l_score=1;
    }else{
        for(int i=left;i<=root-1;i++){
            l_score=create(left,i,root-1);
            if(l_score>l_max){
                l_root=i;
                l_max=l_score;
                for(int j=left;j<=root-1;j++){
                    temp[j]=original[j];
                }
            }
        }
        for(int j=left;j<=root-1;j++)
            original[j]=temp[j];
        original[root].left=l_root;
        l_score=l_max;
    }
    if(right==root){
        original[root].right=0;
        r_score=1;
    }else{
        for(int i=root+1;i<=right;i++){
            r_score=create(root+1,i,right);
            if(r_score>r_max){
                r_root=i;
                r_max=r_score;
                for(int j=root+1;j<=right;j++){
                    temp[j]=original[j];
                }
            }
        }
        for(int j=root+1;j<=right;j++)
            original[j]=temp[j];
        original[root].right=r_root;
        r_score=r_max;
    }
    if(original[root].left==0&&original[root].right==0)
        return original[root].d;
    else 
        return l_score*r_score+original[root].d;
}
int main(){
    int n,root;
    unsigned int score=0,max_score;
    node ans[31];
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>original[i].d;
    for(int i=1;i<=n;i++){
        if((score=create(1,i,n))>max_score){
            max_score=score;
            root=i;
            for(int j=1;j<=n;j++){
                ans[j]=original[j];
            }
        }
    }
    cout<<max_score<<endl;
    preorder(ans,root);
    cout<<endl;
}
