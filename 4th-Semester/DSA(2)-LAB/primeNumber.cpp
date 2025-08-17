#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool checkPrime(int n)
{
    if(n<2){
        return false;
    }
    for(int i=2; i<=sqrt(n); i++)
    {
        if(n%i==0){
            return false;
        }
    }
    return true;
}
int main()
{
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    if(checkPrime(n)== true)
    {
        cout<<n<<" is Prime Number!"<<endl;
    }
    else
    {
        cout<<n<<" is Not Prime Number!"<<endl;
    }
    return 0;
}
