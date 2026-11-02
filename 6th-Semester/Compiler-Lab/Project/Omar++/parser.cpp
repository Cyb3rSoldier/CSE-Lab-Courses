#include "parser.h"

Parser::Parser(std::vector<Token> toks) : tokens(std::move(toks)) {}

// ---------- helpers ----------
const Token& Parser::peek() const { return tokens[current]; }
const Token& Parser::previous() const { return tokens[current - 1]; }
bool Parser::check(TokenType type) const { return peek().type == type; }

const Token& Parser::advance() {
    if (!check(TokenType::END_OF_FILE)) current++;
    return previous();
}

bool Parser::match(TokenType type) {
    if (check(type)) { advance(); return true; }
    return false;
}

const Token& Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw OmarError(peek().line, message + ", but found " + describe(peek()));
}

std::string Parser::describe(const Token& token) const {
    switch (token.type) {
        case TokenType::END_OF_FILE: return "end of file";
        case TokenType::STRING:      return "a text value";
        default:                     return "'" + token.lexeme + "'";
    }
}

// ---------- program / statements ----------
Program Parser::parse() {
    Program program;

    while (!check(TokenType::SHESH) && !check(TokenType::END_OF_FILE)) {
        program.statements.push_back(statement());
    }

    if (!check(TokenType::SHESH)) {
        throw OmarError(peek().line, "missing 'shesh' at the end of the program");
    }
    advance();  // consume 'shesh'

    if (!check(TokenType::END_OF_FILE)) {
        throw OmarError(peek().line, "unexpected code after 'shesh'");
    }
    return program;
}

StmtPtr Parser::statement() {
    if (match(TokenType::DEKHAO)) return printStatement();

    throw OmarError(peek().line,
                    "unexpected " + describe(peek()) +
                    "; a statement must start with 'dekhao'");
}

StmtPtr Parser::printStatement() {
    int line = previous().line;
    ExprPtr value = expression();

    if (!check(TokenType::SEMICOLON)) {
        // report on the line where the statement ended
        throw OmarError(previous().line,
                        "expected ';' after the value, but found " + describe(peek()));
    }
    advance();  // consume ';'
    return std::make_unique<PrintStmt>(std::move(value), line);
}

// ---------- expressions ----------
ExprPtr Parser::expression() {
    ExprPtr left = term();
    while (check(TokenType::JOG) || check(TokenType::BIYOG)) {
        Token op = advance();
        ExprPtr right = term();
        left = std::make_unique<BinaryExpr>(op.type, op.lexeme, std::move(left),
                                            std::move(right), op.line);
    }
    return left;
}

ExprPtr Parser::term() {
    ExprPtr left = unary();
    while (check(TokenType::GUNON) || check(TokenType::VAGFOL) ||
           check(TokenType::VAGSHESH)) {
        Token op = advance();
        ExprPtr right = unary();
        left = std::make_unique<BinaryExpr>(op.type, op.lexeme, std::move(left),
                                            std::move(right), op.line);
    }
    return left;
}

ExprPtr Parser::unary() {
    if (match(TokenType::MINUS)) {
        int line = previous().line;
        ExprPtr operand = unary();
        return std::make_unique<UnaryExpr>(TokenType::MINUS, std::move(operand), line);
    }
    return power();
}

ExprPtr Parser::power() {
    ExprPtr base = primary();
    if (match(TokenType::GHAT)) {
        Token op = previous();
        ExprPtr exponent = unary();  // right-associative: 2 ghat 3 ghat 2 = 2^(3^2)
        return std::make_unique<BinaryExpr>(op.type, op.lexeme, std::move(base),
                                            std::move(exponent), op.line);
    }
    return base;
}

ExprPtr Parser::primary() {
    if (match(TokenType::NUMBER)) {
        return std::make_unique<NumberExpr>(std::stod(previous().lexeme), previous().line);
    }

    if (match(TokenType::STRING)) {
        return std::make_unique<StringExpr>(previous().lexeme, previous().line);
    }

    if (match(TokenType::LPAREN)) {
        ExprPtr inner = expression();
        consume(TokenType::RPAREN, "expected ')' to close the expression");
        return inner;
    }

    if (match(TokenType::MULOK)) {
        int line = previous().line;
        consume(TokenType::LPAREN, "expected '(' after 'mulok'");
        ExprPtr operand = expression();
        consume(TokenType::RPAREN, "expected ')' after the value of 'mulok'");
        return std::make_unique<UnaryExpr>(TokenType::MULOK, std::move(operand), line);
    }

    throw OmarError(peek().line,
                    "expected a number, text, or '(', but found " + describe(peek()));
}
