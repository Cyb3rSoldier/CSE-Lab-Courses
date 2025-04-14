#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int count=0;
    for(int i=0; i<n; i++){
        string word;
        cin>>word;
        if(word=="x++" || word=="++x"){
            count++;
        }
        else if(word== "x--" || word=="--x"){
            count--;
        }
    }
    cout<<count;
    return 0;
}
