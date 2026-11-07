
	int num_lines=0, num_chars=0;
%%
\n	 {++num_lines; ++num_chars;}
.	  {++num_chars;}
%%
int yywrap()
{
	return 1;
}

int main()
{
	
            yyin = fopen( "m.c", "r" );
	    
	yylex();
	printf("no. of lines %d and no. of characters %d\n",num_lines,num_chars);
	return 0;
}