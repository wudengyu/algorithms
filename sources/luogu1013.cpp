#include<iostream>
using namespace std;
string matrix[9][9];
char alphabet[9]={'+','+','+','+','+','+','+','+','+'};
int row[9]={0,0,0,0,0,0,0,0,0};//实际0、1、……等在原表中的行号；
int col[9]={0,0,0,0,0,0,0,0,0};//实际0、1、……等在原表中的列号；
void zero(int length){
    int index;
    for(int i=1;i<length;i++){
        index=i;
        for(int j=1;j<length;j++){
            if(matrix[0][j]!=matrix[i][j]){
                index=0;
                break;
            }
        }
        if(index!=0)
            break;
    }
    alphabet[0]=matrix[index][0].at(0);
    row[0]=index;
    for(int i=0;i<length;i++){
        if(alphabet[0]==matrix[0][i].at(0)){
            col[0]=i;
        }
    }
}
void one(int length){
    for(int i=1;i<length;i++){
        for(int j=1;j<length;j++){
            if(matrix[i][j].length()==2&&matrix[i][j].at(1)==alphabet[0]){
                alphabet[1]=matrix[i][j].at(0);
                for(int k=0;k<length;k++){
                    if(alphabet[1]==matrix[k][0].at(0)){
                        row[1]=k;
                    }
                    if(alphabet[1]==matrix[0][k].at(0)){
                        col[1]=k;
                    }
                }
            }
        }
    }
}
void other(int length){
    for(int x=2;x<length-1;x++){
        alphabet[x]=matrix[row[1]][col[x-1]].at(0);
        for(int k=0;k<length;k++){
            if(alphabet[x]==matrix[k][0].at(0)){
                row[x]=k;
            }
            if(alphabet[x]==matrix[0][k].at(0)){
                col[x]=k;
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>matrix[i][j];
        }
    }
    zero(n);
    one(n);
    other(n);
    for(int i=0;i<n;i++)
        cout<<alphabet[i];
    cout<<endl;
    for(int i=0;i<n;i++)
        cout<<row[i];
    cout<<endl;
    for(int i=0;i<n;i++)
        cout<<col[i];
    cout<<endl;
}