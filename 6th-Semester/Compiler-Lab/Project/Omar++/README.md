# Omar++

A small programming language with Bangla-style keywords, built in C++ for the Compiler Lab.

**Milestone 1 (current):** read an `.omar` file, recognize `dekhao`, evaluate arithmetic, print the result, and report syntax errors with line numbers.

## Build

Requires a C++17 compiler (g++ or clang++).

```bash
g++ -std=c++17 -Wall -Wextra -o omar main.cpp lexer.cpp parser.cpp interpreter.cpp
```

## Run

```bash
./omar examples/hello.omar
./omar examples/calculator.omar
./omar --tokens examples/hello.omar    # also prints the token stream
```

On Windows (MinGW) the executable is `omar.exe`, run as `omar.exe examples\hello.omar`.

## Language syntax (Milestone 1)

Every program is a list of `dekhao` statements and ends with `shesh`.

```
tika this is a comment
dekhao 2 jog 3 gunon 4;
dekhao "Hello";
shesh
```

| Omar++ | Meaning | Example | Result |
|---|---|---|---|
| `dekhao` | print a value | `dekhao 5;` | `5` |
| `jog` | add (or join two texts) | `10 jog 5` | `15` |
| `biyog` | subtract | `10 biyog 3` | `7` |
| `gunon` | multiply | `6 gunon 7` | `42` |
| `vagfol` | divide | `7 vagfol 2` | `3.5` |
| `vagshesh` | remainder | `17 vagshesh 5` | `2` |
| `ghat` | power | `2 ghat 10` | `1024` |
| `mulok(x)` | square root | `mulok(144)` | `12` |
| `-x` | negative number | `-5 jog 8` | `3` |
| `( )` | grouping | `(2 jog 3) gunon 4` | `20` |
| `tika` | comment to end of line | | |
| `shesh` | end of program | | |

Precedence, from lowest to highest: `jog`/`biyog`, then `gunon`/`vagfol`/`vagshesh`, then unary `-`, then `ghat`. `ghat` is right-associative (`2 ghat 3 ghat 2` is `2 ghat 9`).

## Grammar (EBNF)

```
program    -> statement* "shesh"
statement  -> "dekhao" expression ";"
expression -> term   (("jog" | "biyog") term)*
term       -> unary  (("gunon" | "vagfol" | "vagshesh") unary)*
unary      -> "-" unary | power
power      -> primary ("ghat" unary)?
primary    -> NUMBER | STRING | "(" expression ")" | "mulok" "(" expression ")"
```

## How it works

```
source.omar -> Lexer -> tokens -> Parser -> AST -> Interpreter -> output
```

| File | Role |
|---|---|
| `token.h` | token types, `Token`, and the shared `OmarError` |
| `lexer.h/.cpp` | turns source text into tokens, skips `tika` comments |
| `parser.h/.cpp` | AST node definitions and the recursive descent parser |
| `interpreter.h/.cpp` | walks the AST and calculates results |
| `main.cpp` | reads the file and runs the pipeline |

The whole file is lexed and parsed **before** anything runs, so a program with a syntax error prints nothing except the error.
