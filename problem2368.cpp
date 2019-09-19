/*二叉搜索树的和值*/
#include <iostream>
using namespace std;
class binarytree{
    private:
        int value;
        int depth;
        binarytree* left;
        binarytree* right;
    public:
        binarytree(int=0);
        int getvalue(){return value;}
        void setvalue(int v){value=v;}
        void setdepth(int d){depth=d;}
        int add(binarytree*);
};
binarytree::binarytree(int val){
    value=val;
    depth=0;
    left=nullptr;
    right=nullptr;
}
int binarytree::add(binarytree* node){
    if(node->getvalue()<value){
        if(left==nullptr){
            node->setdepth(depth+1);
            left=node;
            return depth+1;
        }else
            return left->add(node);
    }else{
        if(right==nullptr){
            node->setdepth(depth+1);
            right=node;
            return depth+1;
        }else
            return right->add(node);
    }
};
int main(){
    int n,m,sum=0;
    binarytree* tree=nullptr;
    cin>>n;
    tree=new binarytree[n];
    for(int i=0;i<n;i++){
        cin>>m;
        tree[i].setvalue(m);
        if(i>0)
            sum+=tree->add(&tree[i]);
        cout<<sum<<endl;
 }
}