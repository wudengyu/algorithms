#include<iostream>
#include<cstring>
#include<map>
using namespace std;
char matrix[9][9][9];
map<char,int> total;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>matrix[i][j];
        }
    }
    for(int i=1;i<n;i++) {
		total.insert(pair<char,int>(matrix[0][i][0],-1));
	}
	for(int i=1;i<n;i++) {
		for(int j=1;j<n;j++) {
			if(strlen(matrix[i][j])==1){
				total[matrix[i][j][0]]+=1;
			}
		}
	}

    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            int sum=0;
            if(strlen(matrix[i][j])==2){
                sum=total[matrix[i][j][0]]*(n-1)+total[matrix[i][j][1]];
            }else if(strlen(matrix[i][j])==1){
                sum=total[matrix[i][j][0]];
            }else{
                std::cout<<"ERROR!"<<endl;
                return 0;
            }
            if(sum!=total[matrix[i][0][0]]+total[matrix[0][j][0]]){
                std::cout<<"ERROR!"<<endl;
                return 0;
            }
        }
    }
    for(int i=1;i<n;i++)
        std::cout<<matrix[0][i][0]<<"="<<total[matrix[0][i][0]]<<" ";
    std::cout<<endl;
    std::cout<<n-1<<endl;
}