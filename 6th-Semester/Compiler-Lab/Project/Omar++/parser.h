#ifndef OMAR_PARSER_H
#define OMAR_PARSER_H

#include <memory>
#include <string>
#include <vector>

#include "token.h"

// ---------------------------------------------------------------
// AST (Abstract Syntax Tree)
// ---------------------------------------------------------------
struct Expr {
    int line = 0;
    virtual ~Expr() = default;
};
using ExprPtr = std::unique_ptr<Expr>;

struct NumberExpr : Expr {
    double value;
    NumberExpr(double v, int ln) : value(v) { line = ln; }
};

struct StringExpr : Expr {
    std::string value;
    StringExpr(std::string v, int ln) : value(std::move(v)) { line = ln; }
};

// Unary operators: MINUS (-x) and MULOK (square root)
struct UnaryExpr : Expr {
    TokenType op;
    ExprPtr operand;
    UnaryExpr(TokenType o, ExprPtr e, int ln) : op(o), operand(std::move(e)) { line = ln; }
};

// Binary operators: jog, biyog, gunon, vagfol, vagshesh, ghat
struct BinaryExpr : Expr {
    TokenType op;
    std::string opName;  // original word, used in error messages
    ExprPtr left, right;
    BinaryExpr(TokenType o, std::string name, ExprPtr l, ExprPtr r, int ln)
        : op(o), opName(std::move(name)), left(std::move(l)), right(std::move(r)) { line = ln; }
};

struct Stmt {
    int line = 0;
    virtual ~Stmt() = default;
};
using StmtPtr = std::unique_ptr<Stmt>;

struct PrintStmt : Stmt {
    ExprPtr expr;
    PrintStmt(ExprPtr e, int ln) : expr(std::move(e)) { line = ln; }
};

struct Program {
    std::vector<StmtPtr> statements;
};

// ---------------------------------------------------------------
// Parser (recursive descent)
//
// program    -> statement* "shesh"
// statement  -> "dekhao" expression ";"
// expression -> term   (("jog" | "biyog") term)*
// term       -> unary  (("gunon" | "vagfol" | "vagshesh") unary)*
// unary      -> "-" unary | power
// power      -> primary ("ghat" unary)?
// primary    -> NUMBER | STRING | "(" expression ")" | "mulok" "(" expression ")"
// ---------------------------------------------------------------
class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    Program parse();

private:
    std::vector<Token> tokens;
    size_t current = 0;

    const Token& peek() const;
    const Token& previous() const;
    bool check(TokenType type) const;
    bool match(TokenType type);
    const Token& advance();
    const Token& consume(TokenType type, const std::string& message);
    std::string describe(const Token& token) const;

    StmtPtr statement();
    StmtPtr printStatement();

    ExprPtr expression();
    ExprPtr term();
    ExprPtr unary();
    ExprPtr power();
    ExprPtr primary();
};

#endif
