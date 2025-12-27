#include<bits/c++.h>
using namespace std;
int main(){
    int coins = {1,3,5};
    int amount = 8;
    int solution[coins][amount];
    for(int i=0; i<=coins.length;i++){
        for(int j=0; j<=amount; j++){
            if(i == 0 && j == 0){
                solution[i][j] = 1;
            }
            else{
                if(c[i]>j){
                    solution[i][j] = solution[i-1][j];
                }
                else{
                    solution[i][j] = solution[i-1][j]+solution[i][j-c[i];
                }
            }
        }
    }
    cout<<solution;
}
