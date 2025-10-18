#include <bits/stdc++.h>
using namespace std;

int main()
{
    const long long MOD = 1e9 + 7;
    long long n;
    cin >> n;

    long long base = 2, result = 1;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        n /= 2;
    }

    cout << result % MOD << endl;
    return 0;
}
