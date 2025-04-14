#include<iostream>
#include<algorithm>
using namespace std;

int binarySearch(int arr[],int data,int n)
{

    int l=0;
    int r=n-1;
    while (l<=r)
    {
        int mid= (l+r)/2;
        if(data==arr[mid])
        {
            return mid;
        }
        if(data>arr[mid])
        {
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }

    }
    return -1;

}
int main()
{
    int n;
    cout<<"Enter the size of array= ";
    cin>>n;
    cout<<"Enter the values: ";
    int arr[n];
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    sort(arr,arr+n);
    for(int i=0; i<n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    int data;
    cout<<"Enter the value: ";
    cin>>data;
    int variable=binarySearch(arr,data,n);
    if(variable==-1)
    {
        cout<<"Variable not found";
    }
    else
    {
        cout<<variable;
    }
    return 0;
}
