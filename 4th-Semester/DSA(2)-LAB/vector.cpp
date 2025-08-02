#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int>v = {2,3,4,7};
    vector<int>v2(10);
    int i;

    //push value in back
    v.push_back(19);
    v.push_back(10);
    v.push_back(8);
    v.push_back(99);
    v[1]=50;

    //delete from back
    v.pop_back();
    reverse(v.begin(),v.end(),100);

    v2.push_back(10);
    v2.push_back(20);
    v2.insert(v2.begin()+5,5);

    //push value in given index
    v.insert(v.begin()+2,6);

    auto it = find(v.begin(),v.end(),5);
    printf("%d\n",it);
    if(it!=v.end()){
        v.erase(it);
    }

    //size of vector
    cout<<"size of vector: "<<v.size()<<endl;

    //print vector v
    for(int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    //print vector v2
    for(int i= 0 ; i<v2.size(); i++)
    {
        cout<<v2[i]<<" ";
    }
    return 0;
}
