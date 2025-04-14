#include<iostream>
using namespace std;
int main(){
    int a,b,c;
    cout<<"Enter the value of a: ";
    cin>>a;
    cout<<"Enter the value of b: ";
    cin>>b;
    cout<<"Enter the value of c: ";
    cin>>c;
    cout<<"A = "<<a;
    cout<<"\nB = "<<b;
    cout<<"\nC = "<<c;
    cout<<"\n";
    if(a>b && a>c){
        cout<<"A is greater";
    }
    else if(b>a && b>c){
        cout<<"B is greater";
    }
    else{
        cout<<"C is greater";
    }
    return 0;
}