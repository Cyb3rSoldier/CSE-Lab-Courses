#include<iostream>
using namespace std;
int main(){

    int x;
    cin>>x;
    int y[x];
    int count=0;
    for(int i=0; i<x; i++){
        cin>>y[i];
    }
    for(int i=0; i<x; i++){
        if(y[i] == 1){
            count++;
        }
    }
    if(count == 0){
        cout<<"EASY";
    }
    else{
        cout<<"HARD";
    }
    return 0;
}
