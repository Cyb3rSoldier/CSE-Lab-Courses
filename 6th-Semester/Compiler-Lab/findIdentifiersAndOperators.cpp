#include<iostream>
#include<string>
#include<cctype>
using namespace std;
int main(){
    string s;
    cout<<"Enter the code: ";
    getline(cin,s );
    for(int i = 0 ; i<s.length(); i++){
        if(s[i]>='a' && s[i]<='z'){
            string n = "";
            while(s[i] >= 'a' && s[i] <= 'z'){
                n+=s[i];
                i++;
            }
            cout<<n<<" -> "<<"Identifier"<<endl;
            i--;
        }
        else if(s[i] == '+' || s[i]=='-' || s[i] == '*' || s[i] == '/' || s[i] == '='){
            cout<<s[i]<<" -> "<<"Operator"<<endl;
        }
    }

    return 0;
}