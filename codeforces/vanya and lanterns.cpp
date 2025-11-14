#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,l;
    cin>>n>>l;
    vector<int> a(n);
    vector<int>diff(n-1);
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    for(int i=0; i<n-1; i++)
    {
        diff[i] = a[i+1]-a[i];
    }
    float d = *max_element(diff.begin(), diff.end()) / 2.0;
    cout<<d<<endl;
    return 0;
}
