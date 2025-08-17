#include<iostream>
#include<bits/stdc++.h>
#define sz 1
using namespace std;
int a[sz],cnt;

void sieve()
{
    for(int i=4; i<=sz; i+=2)
    {
        a[i]=1;
        for(int i =3; i<sz; i+=2){
            if(a[i]==0){
                for(int j=i*i; j<sz;j+=(i+i)){
                    a[j]=1;
                }
            }
        }
    }

}
int main()
{
    sieve();
    cout<<"Prime number till "<<sz<<": ";
    for(int i=2; i<=sz;i++){
        if(a[i]==0){
            cout<<i<<" ";
            cnt++;
        }
    }
    cout<<endl;
    cout<<"Number of prime number till "<<sz<<": "<<cnt<<endl;

}
