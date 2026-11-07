%{
#include <stdio.h>
%}

%%

auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while {
    printf("%s : KEYWORD\n", yytext);
}

[A-Z][a-z_@#$]*            { printf("%s : VALID ID\n", yytext); }

[a-z_][a-zA-Z0-9_]*        { printf("%s : other word (not a keyword, not a valid ID)\n", yytext); }

[+-]?[0-9]+\.[0-9]+        { printf("%s : FLOATING POINT NUMBER\n", yytext); }

[+]?[0-9]+                 { printf("%s : POSITIVE INTEGER\n", yytext); }

[-][0-9]+                  { printf("%s : NEGATIVE INTEGER\n", yytext); }

[ \t\n]+                   { /* ignore spaces and new lines */ }

.                          { printf("%s : unknown symbol\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Type your input. When finished press Ctrl+Z then Enter:\n");
    yylex();
    return 0;
}