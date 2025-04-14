#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"Size of Array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the array: ";
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    int value;
    cout<<"Enter value to search: ";
    cin>>value;
    int index;
    int flag = false;
    int count =0;
    cout<<"Index: ";
    for(int i=0; i<n; i++)
    {
        if(arr[i]==value)
        {
            index=i;
            flag = true;
            count++;
            if(flag==true)
            {
                cout<<index<<" ";
            }
        }
    }
    cout<<endl;
    if(flag==true)
    {
        cout<<"Number of Existing: ";
        cout<<count;
    }
    else
    {
        cout<<"Value not found";
    }
    return 0;
}
