

%%

.+	{printf("%s\n", yytext);}

%%

int yywrap()
{
	return 1;
}

int main()
{
	
            yyin = fopen( "m.c", "r" );
	    
	yylex();
	return 0;
}