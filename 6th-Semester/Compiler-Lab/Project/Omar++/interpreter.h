#ifndef OMAR_INTERPRETER_H
#define OMAR_INTERPRETER_H

#include <string>

#include "parser.h"

// A runtime value: either a number or a piece of text.
struct Value {
    bool isText = false;
    double number = 0;
    std::string text;

    static Value ofNumber(double n);
    static Value ofText(std::string s);
    std::string toString() const;
};

// Tree-walking interpreter: walks the AST and executes it.
class Interpreter {
public:
    void run(const Program& program);

private:
    Value evaluate(const Expr& expr);
    Value evalUnary(const UnaryExpr& expr);
    Value evalBinary(const BinaryExpr& expr);
};

#endif
