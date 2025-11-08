#include<bits/stdc++.h>
using namespace std;

int dp[10][100];

struct item{
    int value;
    int weight;
};

void fractionalKnapsack(int w,vector<item> &items)
{

    for(int i=1;i<=items.size();i++)
    {
        for(int j=1;j<=w;j++)
            {
            if(items[i-1].weight>j)
            {
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] =max(dp[i-1][j], items[i-1].value + dp[i-1][j-items[i-1].weight]);
            }
        }
    }
    for(int i=0;i<=items.size();i++)
    {
        for(int j=0;j<=w;j++)
            {
            cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }

    //return finalValue;
}

int main()
{
    int w=6,n=5,i;
    vector<item> items(n);
    cout<<"Enter "<<n<<" items (value,weight)"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>items[i].value>>items[i].weight;
    }
    fractionalKnapsack(w,items);
    cout<<"Maximum value in Knapsack is "<<dp[n][w]<<endl;
}

/*
3 2
4 3
5 4
6 5
4 1
*/

