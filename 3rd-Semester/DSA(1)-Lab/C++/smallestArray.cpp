#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the size= ";
    cin>>n;
    int arr[n];
    int small = INT_MAX;
    int large= INT_MIN;
    cout<<"Enter the values= ";
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    for(int i=0; i<n; i++){
        if(arr[i]<small){
            small=arr[i];
        }
    }
    cout<<"Smallest value= "<<small<<endl;
    for(int i=0; i<n; i++){
        if(arr[i]>large){
            large=arr[i];
        }
    }
    cout<<"largest value= "<<large;
    return 0;
}
