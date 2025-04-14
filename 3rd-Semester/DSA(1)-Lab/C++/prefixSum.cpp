#include<iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the Size of Array: ";
    cin>>n;
    cout<<"Enter the values: ";
    int arr[n];
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    int pre[n];
    pre[0]=arr[0];
    for(int i=1; i<n; i++)
    {
        pre[i]=pre[i-1]+arr[i];
    }
    for(int i=0; i<n; i++)
    {
        cout<<pre[i]<<" ";
    }
    cout<<endl;
    int q;
    cout<<"Number of Operations: ";
    cin>>q;
    while(q>0)
    {
        int l,r;
        cin>>l>>r;
        if(l==0)
        {
            cout<<pre[r]<<endl;
        }
        else
        {
            int sum=pre[r]-pre[l-1];
            cout<<sum<<endl;
        }
        q--;
    }
    return 0;
}

