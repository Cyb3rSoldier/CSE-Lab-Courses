#include<bits/stdc++.h>
using namespace std;
#define sz 500

long long dp[sz];
long long fibo_rec(int n)
{
    if(n<2)
    {
        dp[n]=n;
        return n;
    }
    if(dp[n] != -1)
    {
        return dp[n];

    }
    dp[n] = fibo_rec(n-1)+fibo_rec(n-2);
    return dp[n];

}

int main()
{
    int n;
    cout<<"Enter the limit: ";
    cin>>n;
    for(int i = 0 ; i<=n; i++)
    {
        dp[i]= -1;
    }

    /*
    Tabular method
    dp[0] = 0;
    dp[1] = 1;
    for(int i =2; i<=n; i++){
    dp[i] = dp[i-2] + dp[i-1];
    }
    */

    fibo_rec(n);
    for(int i =0; i<=n ; i++)
    {
        cout<<dp[i]<<" ";
    }
    cout<<endl;
    cout<<"Fibonacci of "<<n<<" is "<<dp[n]<<endl;
    return 0;
}
