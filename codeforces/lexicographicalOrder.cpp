#include<iostream>
using namespace std;
int main(){
    string s1,s2;
    cin>>s1>>s2;
    for(int i=0; i<s1.size();i++){
        if(s1[i]>='A' && s1[i]<='Z'){
            s1[i]+=32;
        }
        if(s2[i]>='A' && s2[i]<='Z'){
            s2[i]+=32;
        }
    }
    if(s1<s2){
        cout<<"-1";
    }
    else if(s1>s2){
        cout<<"1";
    }
    else if(s1==s2){
        cout<<"0";
    }
    return 0;
}
