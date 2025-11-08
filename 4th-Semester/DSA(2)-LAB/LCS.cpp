#include<bits/stdc++.h>
using namespace std;

int dp[100][100];

int main()
{
    string s1,s2;
    int n,m;
    cout<<"Enter first string: ";
    cin>>s1;
    cout<<"Enter second string: ";
    cin>>s2;
    n=s1.size();
    m=s2.size();
    for(int i=0; i<=n; i++)
        dp[0][i]=0;
    for(int i=0; i<=m; i++)
        dp[i][0]=0;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j]=1+dp[i-1][j-1];
            }
            else
            {
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=m; j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"LCS of "<<s1<<" & "<<s2<<" is "<<dp[n][m]<<endl;

    return 0;
}
