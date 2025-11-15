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
    int max_gap = 0;
    if(n>1)
    {
        max_gap = *max_element(diff.begin(),diff.end());
    }
    double d = max({(double)a[0], (double)l-a[n-1], max_gap /2.0 });
    cout << fixed << setprecision(10) << d << endl;

    return 0;
}
