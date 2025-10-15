#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    int u = 0;
    int l = 0;
    for(int i=0; i<s.size();i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            u++;
        }
        else if(s[i] >= 'a' && s[i] <= 'z'){
            l++;
        }
    }
    for(int i=0; i<s.size();i++){
        if(u>l){
            if(s[i] >= 'a' && s[i] <= 'z'){
                s[i] = s[i]-32;
            }
        }
        else if(l>u){
            if(s[i] >= 'A' && s[i] <= 'Z'){
                s[i] = s[i]+32;
            }
        }
        else if(u==l){
            if(s[i] >= 'A' && s[i] <= 'Z'){
                s[i] = s[i]+32;
            }
        }
    }
    for(int i=0; i<s.size();i++){
        cout<<s[i];
    }
    return 0;
}
