#include<iostream>
using namespace std;
int main(){
    int a,b;
    int lcm;
    cout<<"Enter two numbers: ";
    cin>>a>>b;
    for(int i=1; i<max(a,b);i++){
        if(a*i == b*i){
            lcm=i;
            break;
        }
    }
    cout<<"LCM is: "<<lcm;
    return 0;
}
