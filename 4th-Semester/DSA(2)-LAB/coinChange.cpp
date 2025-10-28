#include<bits/stdc++.h>
#define sz 1000
using namespace std;

int dp[11][sz];

int main()
{
    int coin[]= {1,2,5,10,20,50,100,200,500,1000};
    int amount = 775,i,j,n;
    n=sizeof(coin)/sizeof(coin[0]);
    cout<<n<<endl;
    sort(coin,coin+n);
    for(i=0; i<n; i++)
    {
        for(j=1; j<=amount; j++)
        {
            if(j>=coin[i]&&i==0)
            dp[i][j]=1+dp[i][j-coin[i]];
            else if(j>=coin[i]&&i>0)
            dp[i][j]=min(dp[i-1][j],1+dp[i][j-coin[i]]);
            else if(i>0) dp[i][j]=dp[i-1][j];
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<=amount; j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<dp[n-1][amount];
}

