#include <iostream>
#include<cmath>
using namespace std;

int main() {
    int x,a,b;
    cin>>x>>a>>b;
    if(x<a){
        cout<<0;
    }
    else if(a<=x && x<=b){
        cout<<abs(x);
    }
    else if(x>b){
        cout<<x*x;
    }
    cout<<endl;
    return 0;
}
