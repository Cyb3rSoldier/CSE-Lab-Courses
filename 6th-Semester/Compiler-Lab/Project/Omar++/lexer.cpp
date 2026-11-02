#include "lexer.h"

#include <cctype>
#include <unordered_map>

// Keyword table: if a word is in this map it is a keyword,
// otherwise it becomes an IDENTIFIER.
static const std::unordered_map<std::string, TokenType> keywords = {
    {"dekhao",   TokenType::DEKHAO},
    {"jog",      TokenType::JOG},
    {"biyog",    TokenType::BIYOG},
    {"gunon",    TokenType::GUNON},
    {"vagfol",   TokenType::VAGFOL},
    {"vagshesh", TokenType::VAGSHESH},
    {"ghat",     TokenType::GHAT},
    {"mulok",    TokenType::MULOK},
    {"shesh",    TokenType::SHESH},
};

Lexer::Lexer(std::string source) : src(std::move(source)) {}

bool Lexer::atEnd() const { return pos >= src.size(); }

char Lexer::peek(size_t offset) const {
    return (pos + offset < src.size()) ? src[pos + offset] : '\0';
}

char Lexer::advance() { return src[pos++]; }

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!atEnd()) {
        char c = peek();

        if (c == '\n') { line++; advance(); continue; }
        if (c == ' ' || c == '\t' || c == '\r') { advance(); continue; }

        if (std::isdigit(static_cast<unsigned char>(c))) {
            tokens.push_back(number());
            continue;
        }

        if (c == '"') {
            tokens.push_back(text());
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            Token t = word();
            if (t.lexeme == "tika") {   // comment: skip to end of line
                skipComment();
                continue;
            }
            tokens.push_back(t);
            continue;
        }

        switch (c) {
            case '(': tokens.push_back({TokenType::LPAREN,    "(", line}); advance(); break;
            case ')': tokens.push_back({TokenType::RPAREN,    ")", line}); advance(); break;
            case ';': tokens.push_back({TokenType::SEMICOLON, ";", line}); advance(); break;
            case '-': tokens.push_back({TokenType::MINUS,     "-", line}); advance(); break;
            default:
                throw OmarError(line, std::string("unexpected character '") + c + "'");
        }
    }

    tokens.push_back({TokenType::END_OF_FILE, "", line});
    return tokens;
}

Token Lexer::number() {
    size_t start = pos;
    while (std::isdigit(static_cast<unsigned char>(peek()))) advance();

    // decimal part: only if '.' is followed by a digit
    if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peek(1)))) {
        advance();
        while (std::isdigit(static_cast<unsigned char>(peek()))) advance();
    }
    return {TokenType::NUMBER, src.substr(start, pos - start), line};
}

Token Lexer::text() {
    int startLine = line;
    advance();  // opening quote
    std::string value;

    while (!atEnd() && peek() != '"') {
        char c = advance();
        if (c == '\n') {
            throw OmarError(startLine, "unterminated text (missing closing '\"')");
        }
        if (c == '\\') {  // escape sequences
            if (atEnd()) break;
            char e = advance();
            switch (e) {
                case 'n':  value += '\n'; break;
                case 't':  value += '\t'; break;
                case '"':  value += '"';  break;
                case '\\': value += '\\'; break;
                default:
                    throw OmarError(line, std::string("unknown escape sequence '\\") + e + "'");
            }
        } else {
            value += c;
        }
    }

    if (atEnd()) {
        throw OmarError(startLine, "unterminated text (missing closing '\"')");
    }
    advance();  // closing quote
    return {TokenType::STRING, value, startLine};
}

Token Lexer::word() {
    size_t start = pos;
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') advance();
    std::string lexeme = src.substr(start, pos - start);

    auto it = keywords.find(lexeme);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    return {type, lexeme, line};
}

void Lexer::skipComment() {
    while (!atEnd() && peek() != '\n') advance();
}
