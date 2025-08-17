#include<iostream>
using namespace std;
int gcd(int a, int b){
    if(b==0){
        return a;
    }
    gcd(b,a%b);
}
int main()
{
    int a,b;
    cout<<("Enter 2 numbers: ");
    cin>>a>>b;
    /*while(b!=0)
    {
        int temp = a%b;
        a=b;
        b=temp;
        gcd = a;
    }*/

    //recursive call
    cout<<"GCD is: "<<gcd(a,b)<<endl;
    int lcm = abs(a*b)/gcd(a,b);
    cout<<"LCM is: "<<lcm<<endl;
    return 0;
}
