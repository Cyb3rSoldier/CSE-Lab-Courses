#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string* names = new string[n];
    int* counts = new int[n]();
    int total = 0;

    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;

        int found = -1;
        for (int j = 0; j < total; j++)
        {
            if (names[j] == name)
            {
                found = j;
                break;
            }
        }

        if (found == -1)
        {
            names[total] = name;
            counts[total] = 1;
            total++;
            cout << "OK" << endl;
        }
        else
        {
            int c = counts[found];
            string newName = name + to_string(c);
            cout << newName << endl;
            names[total] = newName;
            counts[total] = 1;

            total++;
            counts[found]++;
        }
    }
    delete[] names;
    delete[] counts;
    return 0;
}
