#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    string line;
    cout << "Enter the code: " << endl;
    while (true)
    {
        getline(cin, line);

        if (line == "end")
            break;

        s += line;
        s += " ";
    }

    cout << "Output: " << endl;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            string n = "";
            while (s[i] >= 'a' && s[i] <= 'z')
            {
                n += s[i];
                i++;
            }
            if (n == "int" || n == "float" || n == "double" || n == "char" || n == "string" ||
                n == "for" || n == "if" || n == "else if" || n == "else" || n == "while" || n == "return 0")
            {
                cout << n << " -> " << "key word" << endl;
            }
            else
            {
                cout << n << " -> " << "Identifier" << endl;
            }
            i--;
        }
        else if ((s[i] == '+' && s[i + 1] == '+') || (s[i] == '-' && s[i + 1] == '-'))
        {
            cout << s[i] << s[i + 1] << " -> " << "Increment/Decrement Operator" << endl;
            i++;
            continue;
        }
        else if ((s[i] == '&' && s[i + 1] == '&') || (s[i] == '|' && s[i + 1] == '|'))
        {
            cout << s[i] << s[i + 1] << " -> " << "Logical Operator" << endl;
            i++;
            continue;
        }
        else if ((s[i] == '=' && s[i + 1] == '=') || (s[i] == '!' && s[i + 1] == '=') || (s[i] == '>' && s[i + 1] == '=') || (s[i] == '<' && s[i + 1] == '='))
        {
            cout << s[i] << s[i + 1] << " -> " << "Relational Operator" << endl;
            i++;
            continue;
        }
        else if (s[i] == '>' || s[i] == '<')
        {
            cout << s[i] << s[i + 1] << " -> " << "Relational Operator" << endl;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
        {
            cout << s[i] << " -> " << "Arithmetic Operator" << endl;
        }
        else if (s[i] == '=')
        {
            cout << s[i] << " -> " << "Assignment Operator" << endl;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            string n = "";
            while (s[i] >= '0' && s[i] <= '9')
            {
                n += s[i];
                i++;
            }
            cout << n << " -> " << "constant" << endl;
            i--;
        }
    }

    return 0;
}
