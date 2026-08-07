#include <iostream>
using namespace std;

int main()
{
    string s;
    int c[26] = {0};
    cout << "Enter a String: ";
    cin >> s;
    for (char ch : s)
    {
        c[ch - 'a']++;
    }
    for (char ch : s)
    {
        if (c[ch - 'a'] == 1)
        {
            cout << ch << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}