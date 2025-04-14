#include<iostream>
#include<algorithm>
using namespace std;
int binarySearch(int arr[],int value,int n)
{
    int l=0;
    int r= n-1;
    while(l<=r)
    {
        int mid= (l+r)/2;
        if(value==arr[mid])
        {
            return mid;
        }
        if(value>arr[mid])
        {
            l= mid+1;
        }
        else
        {
            r= mid-1;
        }

    }
    return -1;
}
int main()
{
    int n;
    cout<<"Size of Array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the array: ";
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    sort(arr,arr+n);
    cout<<"Sorted Result: ";
    for(int i=0; i<n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    int value;
    cout<<"Enter value to search: ";
    cin>>value;
    int result= binarySearch(arr,value,n);
    if(result==-1){
        cout<<"Value not found";
    }
    else{
        cout<<"Index: "<<result;
    }
    return 0;
}
