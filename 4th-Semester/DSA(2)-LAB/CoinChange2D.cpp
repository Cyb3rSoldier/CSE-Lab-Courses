#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, V;
    cout << "Enter number of coins: ";
    cin >> n;
    vector<int> coins(n);
    cout << "Enter coin values: ";
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    cout << "Enter total value: ";
    cin >> V;

    const int INF = 1e9; // a large number
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, INF));

    // Base case: 0 value can be made with 0 coins
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;

    // Fill the table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= V; j++) {
            if (coins[i - 1] <= j)
                dp[i][j] = min(1 + dp[i][j - coins[i - 1]], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    if (dp[n][V] == INF)
        cout << "Not possible to make value " << V << endl;
    else
        cout << "Minimum coins required = " << dp[n][V] << endl;



    return 0;
}

