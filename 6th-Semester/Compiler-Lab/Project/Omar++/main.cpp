#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

static void printUsage() {
    std::cerr << "Usage: omar [--tokens] <file.omar>\n"
              << "  --tokens   print the token stream before running\n";
}

int main(int argc, char* argv[]) {
    bool showTokens = false;
    std::string path;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--tokens") showTokens = true;
        else path = arg;
    }

    if (path.empty()) {
        printUsage();
        return 1;
    }

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: cannot open file '" << path << "'\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    try {
        // 1. Lexing
        Lexer lexer(buffer.str());
        std::vector<Token> tokens = lexer.tokenize();

        if (showTokens) {
            for (const Token& t : tokens) {
                std::cout << "[line " << t.line << "] " << tokenTypeName(t.type);
                if (!t.lexeme.empty()) std::cout << "  '" << t.lexeme << "'";
                std::cout << "\n";
            }
            std::cout << "----\n";
        }

        // 2. Parsing (the whole file is checked before anything runs)
        Parser parser(tokens);
        Program program = parser.parse();

        // 3. Execution
        Interpreter interpreter;
        interpreter.run(program);
    } catch (const OmarError& e) {
        std::cerr << "Error [line " << e.line() << "]: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
