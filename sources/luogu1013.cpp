#include<iostream>
using namespace std;
string matrix[9][9];
char row[9],col[9];
int zero(int length){
    int rindex=0,cindex=0;
    for(int i=1;i<length;i++){
        rindex=i;
        for(int j=1;j<length;j++){
            if(matrix[0][j]!=matrix[i][j]){
                rindex=0;
                break;
            }
        }
        if(rindex!=0)
            break;
    }
    for(int i=1;i<length;i++){
        cindex=i;
        for(int j=1;j<length;j++){
            if(matrix[j][0]!=matrix[j][i]){
                cindex=0;
                break;
            }
        }
        if(cindex!=0)
            break;
    }
    return matrix[0][rindex]==matrix[cindex][0]?rindex:0;
}

int main(){

    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>matrix[i][j];
        }
    }
    cout<<zero(n)<<endl;

}