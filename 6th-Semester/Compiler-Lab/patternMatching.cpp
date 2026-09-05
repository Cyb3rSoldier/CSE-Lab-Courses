#include<iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string n;
    int l;
    cout << "Enter the limit: ";
    cin >> l;
    for (int i = 0; i < l; i++)
    {
        cout << "Input: ";
        cin >> n;
        cout << "Output: ";
        int ns = n.size();
        string temp, temp2;
        if (n[0] == '(' && n[ns - 2] == ')' && n[ns - 1] == '*')
        {
            cout << "epsilon , ";
            temp += n[1];
            temp += n[2];
            temp2 = temp;
            for (int i = 0; i <= 3; i++)
            {
                cout << temp2 << " , ";
                temp2 += temp;
            }
            cout << " ... ";
        }

        else if (n[1] != '?' && n[ns - 1] == '+')
        {
            temp += n[0];
            temp += n[1];
            for (int i = 0; i <= 3; i++)
            {
                cout << temp << " , ";
                temp += n[1];
            }
            cout << " ... ";
        }

        else if (n[1] == '?' && n[ns - 1] == '+')
        {
            cout << n[2] << " , ";
            temp += n[ns - 2];
            for (int i = 0; i <= 3; i++)
            {
                cout << n[0] << temp << " , ";
                temp += n[ns - 2];
            }
            cout << " ... ";
        }

        else if (n[1] == '+')
        {
            temp += n[0];
            temp2 = temp;
            for (int i = 0; i <= 3; i++)
            {
                cout << temp2 << n[2] << " , ";
                temp2 += temp;
            }
            cout << " ... ";
        }
        else
        {
            cout << "Invalid Input!";
        }
        cout << endl;
    }
    return 0;
}