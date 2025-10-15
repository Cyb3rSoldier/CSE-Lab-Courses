#include<bits/stdc++.h>
using namespace std;

int main()
{
    int matrix[5][5];
    int row, col;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> matrix[i][j];
            if (matrix[i][j] == 1)
            {
                row = i + 1;
                col = j + 1;
            }
        }
    }
    int count = abs(3 - row) + abs(3 - col);
    cout<<count<<endl;
    return 0;
}
