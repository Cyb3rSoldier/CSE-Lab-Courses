#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, amount;
    cout << "Enter number of coins: ";
    cin >> n;
    vector<int> coins(n);
    cout << "Enter coin values: ";
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    cout << "Enter amount: ";
    cin >> amount;

    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0; // 0 coins to make 0

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] = min(dp[j], 1 + dp[j - coins[i]]);
        }
    }

    if (dp[amount] == INF)
        cout << "Not possible to make amount " << amount << endl;
    else
        cout << "Minimum coins required = " << dp[amount] << endl;

    return 0;
}

