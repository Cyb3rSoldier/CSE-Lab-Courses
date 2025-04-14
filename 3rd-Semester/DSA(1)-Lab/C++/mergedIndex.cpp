#include<iostream>
using namespace std;
int main(){
    int n1,n2;
    cout<<"Enter the size of first array: ";
    cin>>n1;
    cout<<"Enter first array: ";
    int arr1[n1];
    for(int i=0;i<n1;i++){
        cin>>arr1[i];
    }
    cout<<"Enter the size of second array: ";
    cin>>n2;
    cout<<"Enter second array: ";
    int arr2[n2];
    for(int i=0; i<n2; i++){
        cin>>arr2[i];
    }
    int arr3[n1+n2];
    cout<<"Merged Array: ";
    for(int i=0; i<n1; i++){
        arr3[i]=arr1[i];
    }
    int j= n1;
    for(int i=0;i<n2; i++){
        arr3[j]=arr2[i];
        j++;
    }
    for (int i=0; i<(n1+n2); i++){
        cout<<arr3[i]<<" ";
    }
    return 0;
}
