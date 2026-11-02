
#include <iostream>
#include <string>
using namespace std;

bool NUM(char n) {
    return (n >= '0' && n <= '9');
}

bool OP(char n) {
    return (n == '+' || n == '-' || n == '*' || n == '/');
}

int main() {
    string exp;
    cout << "Enter the Expression: ";
    getline(cin, exp);

    int brackets = 0;
    bool valid = true;
    bool expectNumber = true;
    cout<<"Output: ";

    for (int i = 0; i < exp.size(); i++) {
        char ch = exp[i];

        if (NUM(ch)) {
            if (!expectNumber) {
                valid = false;
                break;
            }
            expectNumber = false;
        }
        else if (ch == '(') {
            if (!expectNumber) {
                valid = false;
                break;
            }
            brackets++;
        }
        else if (ch == ')') {
            if (expectNumber || brackets == 0) {
                valid = false;
                break;
            }
            brackets--;
            expectNumber = false;
        }
        else if (OP(ch)) {
            if (expectNumber) {
                valid = false;
                break;
            }
            expectNumber = true;
        }
        else {
            valid = false;
            break;
        }
    }

    if (brackets != 0 || expectNumber || exp.empty()) {
        valid = false;
    }

    if (valid) {
        cout << "VALID!";
    }
    else {
        cout << "INVALID!";
    }

    return 0;
}
