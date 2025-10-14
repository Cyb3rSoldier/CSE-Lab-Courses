#include<iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    string digit = "";
    for (int i =0; i<s.size();i++)
    {
        if (s[i] != '+')
        {
            digit += s[i];
        }
    }

    sort(digit.begin(),digit.end());

    for(int i=0; i<digit.size(); i++)
    {
        cout<<digit[i];
        if(i != digit.size()-1){
            cout<<"+";
        }
    }
    return 0;
}
