#ifndef OMAR_LEXER_H
#define OMAR_LEXER_H

#include <string>
#include <vector>

#include "token.h"

// Converts Omar++ source text into a list of tokens.
class Lexer {
public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t pos = 0;
    int line = 1;

    bool atEnd() const;
    char peek(size_t offset = 0) const;
    char advance();

    Token number();
    Token text();
    Token word();
    void skipComment();
};

#endif
