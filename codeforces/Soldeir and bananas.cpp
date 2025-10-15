#include<bits/stdc++.h>
using namespace std;
int main(){
    int k,n,w;
    cin>>k>>n>>w;
    int borrow = 0;
    int sum = 0;
    for(int i=1; i<=w; i++){
        sum = sum+(i*k);
    }
    if(sum<=n){
        borrow = 0;
    }
    else{
        borrow = sum-n;
    }
    cout<<borrow;
    return 0;
}
