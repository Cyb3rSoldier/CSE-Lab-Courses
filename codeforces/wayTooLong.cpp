#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        string word;
        cin>>word;
        if(word.length()>10){
            cout<<word.front()<<word.length()-2<<word.back()<<"\n";
        }
        else{
            cout<<word<<"\n";
        }
    }

    return 0;
}
