#include<iostream>
using namespace std;
int main()
{
    int a,b;
    cout<<("Enter 2 numbers: ");
    cin>>a>>b;
    int gcd = 1;
    int min_num = min(a,b);
    for(int i=1; i<=min_num;i++){
        if(a%i==0 && b%i==0){
            gcd=i;
        }
    }
    cout<<"GCD is: "<<gcd;
    return 0;
}
