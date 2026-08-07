#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cout << "Enter the number of strings: ";
    cin >> n;

    vector<string> words(n);

    cout << "Enter the strings:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
    }

    unordered_map<string, vector<string>> mp;

    for (string word : words)
    {
        string key = word;
        sort(key.begin(), key.end());
        mp[key].push_back(word);
    }

    cout << "Grouped Anagrams:\n";

    for (auto group : mp)
    {
        cout << "[ ";
        for (string word : group.second)
        {
            cout << word << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}