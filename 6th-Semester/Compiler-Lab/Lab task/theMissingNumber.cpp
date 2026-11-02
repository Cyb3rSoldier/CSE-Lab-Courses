#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"Enter Limit: ";
    cin>>n;
    int arr[n];
    int sum = 0;
    int sum1 = 0;

    cout<<"nums = ";
    for(int i = 0; i<n; i++){
        cin>>arr[i];
        sum = arr[i]+sum;
    }

    for(int i =1; i<=n; i++){
        sum1 = i+sum1;
    }

    int res = sum1-sum;
    cout<<res;


    return 0;
}