#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Helper: check if character is a digit
bool NUM(char n) {
  return isdigit(static_cast<unsigned char>(n));
}

// Helper: check if character is an arithmetic operator
bool OP(char n) {
  return n == '+' || n == '-' || n == '*' || n == '/';
}

// Helper: check if character is a parenthesis
bool BRAC(char n) {
  return n == '(' || n == ')';
}

// Validates infix mathematical expression syntax
bool isValidExpression(const string& exp) {
  if (exp.empty()) return false;

  int n = static_cast<int>(exp.size());
  int openCount = 0;

  // Rule 1: Expression cannot start or end with a binary operator
  if (OP(exp[0]) || OP(exp[n - 1])) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    char curr = exp[i];

    if (curr == '(') {
      openCount++;
      // Cannot have empty brackets `()` or operator immediately after `(`
      if (i + 1 < n && (exp[i + 1] == ')' || OP(exp[i + 1]))) {
        return false;
      }
    } else if (curr == ')') {
      openCount--;
      // Closing bracket cannot appear without a preceding open bracket
      if (openCount < 0) {
        return false;
      }
      // Closing bracket cannot be directly followed by a number or '(' without an operator
      if (i + 1 < n && (NUM(exp[i + 1]) || exp[i + 1] == '(')) {
        return false;
      }
    } else if (OP(curr)) {
      // Operator must be followed by a number or '('
      if (i + 1 < n && !(NUM(exp[i + 1]) || exp[i + 1] == '(')) {
        return false;
      }
    } else if (NUM(curr)) {
      // Number cannot be followed immediately by '(' without an explicit operator
      if (i + 1 < n && exp[i + 1] == '(') {
        return false;
      }
    } else {
      // Invalid character (spaces, unrecognized symbols)
      return false;
    }
  }

  // All open brackets must be matched
  return openCount == 0;
}

int main() {
  string exp;
  cout << "Enter the expression: ";
  if (!getline(cin, exp)) {
    return 0;
  }
  cout << endl;

  if (isValidExpression(exp)) {
    cout << "VALID" << endl;
  } else {
    cout << "INVALID" << endl;
  }

  return 0;
}