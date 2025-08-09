#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    map<char,int>mp;
    string s= "0l000uuAAAuitrer.%^";
    int i;
    for(int i=0; i<s.size(); i++)
    {
        mp[s[i]]++;
    }
    map<char,int>::iterator it;
    cout<<"Frequency of corresponding character"<<endl;
    for(it=mp.begin(); it!=mp.end(); it++)
    {
        cout<<it->first<<": "<<it->second<<endl;
    }
    return 0;
}


