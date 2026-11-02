#include "interpreter.h"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>

// ---------- Value ----------
Value Value::ofNumber(double n) {
    Value v;
    v.number = n;
    return v;
}

Value Value::ofText(std::string s) {
    Value v;
    v.isText = true;
    v.text = std::move(s);
    return v;
}

std::string Value::toString() const {
    if (isText) return text;

    double v = number;
    if (v == 0) v = 0.0;  // avoid printing "-0"

    // whole numbers print without a decimal point: 7 instead of 7.0
    if (std::floor(v) == v && std::fabs(v) < 1e15) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%.0f", v);
        return buf;
    }

    std::ostringstream out;
    out.precision(10);
    out << v;
    return out.str();
}

// ---------- Interpreter ----------
void Interpreter::run(const Program& program) {
    for (const StmtPtr& stmt : program.statements) {
        if (const auto* print = dynamic_cast<const PrintStmt*>(stmt.get())) {
            Value v = evaluate(*print->expr);
            std::cout << v.toString() << "\n";
        }
    }
}

Value Interpreter::evaluate(const Expr& expr) {
    if (const auto* n = dynamic_cast<const NumberExpr*>(&expr)) {
        return Value::ofNumber(n->value);
    }
    if (const auto* s = dynamic_cast<const StringExpr*>(&expr)) {
        return Value::ofText(s->value);
    }
    if (const auto* u = dynamic_cast<const UnaryExpr*>(&expr)) {
        return evalUnary(*u);
    }
    if (const auto* b = dynamic_cast<const BinaryExpr*>(&expr)) {
        return evalBinary(*b);
    }
    throw OmarError(expr.line, "internal error: unknown expression");
}

Value Interpreter::evalUnary(const UnaryExpr& expr) {
    Value operand = evaluate(*expr.operand);

    if (operand.isText) {
        const char* name = (expr.op == TokenType::MULOK) ? "mulok" : "-";
        throw OmarError(expr.line, std::string("'") + name + "' only works on numbers");
    }

    if (expr.op == TokenType::MINUS) {
        return Value::ofNumber(-operand.number);
    }

    // MULOK (square root)
    if (operand.number < 0) {
        throw OmarError(expr.line, "cannot take 'mulok' of a negative number");
    }
    return Value::ofNumber(std::sqrt(operand.number));
}

Value Interpreter::evalBinary(const BinaryExpr& expr) {
    Value left = evaluate(*expr.left);
    Value right = evaluate(*expr.right);

    // 'jog' can also join two texts together
    if (expr.op == TokenType::JOG && left.isText && right.isText) {
        return Value::ofText(left.text + right.text);
    }

    if (left.isText || right.isText) {
        throw OmarError(expr.line, "'" + expr.opName + "' needs two numbers" +
                        (expr.op == TokenType::JOG ? " (or two texts)" : ""));
    }

    double a = left.number, b = right.number;

    switch (expr.op) {
        case TokenType::JOG:   return Value::ofNumber(a + b);
        case TokenType::BIYOG: return Value::ofNumber(a - b);
        case TokenType::GUNON: return Value::ofNumber(a * b);
        case TokenType::VAGFOL:
            if (b == 0) throw OmarError(expr.line, "division by zero");
            return Value::ofNumber(a / b);
        case TokenType::VAGSHESH:
            if (b == 0) throw OmarError(expr.line, "modulus by zero");
            return Value::ofNumber(std::fmod(a, b));
        case TokenType::GHAT: {
            double r = std::pow(a, b);
            if (!std::isfinite(r)) throw OmarError(expr.line, "invalid result for 'ghat'");
            return Value::ofNumber(r);
        }
        default:
            throw OmarError(expr.line, "internal error: unknown operator");
    }
}
