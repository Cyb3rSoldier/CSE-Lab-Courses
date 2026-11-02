#ifndef OMAR_TOKEN_H
#define OMAR_TOKEN_H

#include <stdexcept>
#include <string>

// All kinds of tokens the lexer can produce (Milestone 1 subset).
enum class TokenType {
    // keywords
    DEKHAO,    // print
    JOG,       // +
    BIYOG,     // -
    GUNON,     // *
    VAGFOL,    // /
    VAGSHESH,  // %
    GHAT,      // power
    MULOK,     // square root
    SHESH,     // end program

    // literals
    NUMBER,
    STRING,

    // symbols
    MINUS,     // '-' (only used as unary minus, e.g. -5)
    LPAREN,
    RPAREN,
    SEMICOLON,

    // other
    IDENTIFIER,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

// One error type shared by the lexer, parser and interpreter.
class OmarError : public std::runtime_error {
public:
    OmarError(int line, const std::string& message)
        : std::runtime_error(message), line_(line) {}
    int line() const { return line_; }

private:
    int line_;
};

// Human-readable token name (used by the --tokens option).
inline std::string tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::DEKHAO:      return "DEKHAO";
        case TokenType::JOG:         return "JOG";
        case TokenType::BIYOG:       return "BIYOG";
        case TokenType::GUNON:       return "GUNON";
        case TokenType::VAGFOL:      return "VAGFOL";
        case TokenType::VAGSHESH:    return "VAGSHESH";
        case TokenType::GHAT:        return "GHAT";
        case TokenType::MULOK:       return "MULOK";
        case TokenType::SHESH:       return "SHESH";
        case TokenType::NUMBER:      return "NUMBER";
        case TokenType::STRING:      return "STRING";
        case TokenType::MINUS:       return "MINUS";
        case TokenType::LPAREN:      return "LPAREN";
        case TokenType::RPAREN:      return "RPAREN";
        case TokenType::SEMICOLON:   return "SEMICOLON";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
    }
    return "UNKNOWN";
}

#endif
