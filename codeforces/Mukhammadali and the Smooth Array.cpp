#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n;
    cin>>t;
    while (t > 0)
    {
        cin>>n;
        vector<int>a(n),c(n);
        for(int i= 0; i<n; i++)
        {
            cin>>a[i];
        }
        for(int i= 0; i<n; i++)
        {
            cin>>c[i];
        }
        /*vector<int> sortA = a;
        sort(sortA.begin(), sortA.end());
        if(sortA==a)
        {
            cout<<0;
        }*/
        long long total_cost = 0;

        for(int i = 1; i < n; i++) {
            if(a[i] < a[i-1]) {
                // If drop happens, change current element to previous
                total_cost += c[i];
                a[i] = a[i-1]; // make it non-decreasing
            }
        }

        cout << total_cost << "\n";



        t--;
    }
    return 0;
}
