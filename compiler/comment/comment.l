%{
#include <stdio.h>
%}
%%
"/*"(.|\n)*"*/" {
        printf("Matched Comment: %s\n",yytext);
    }
\n 
. 
%%
int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen( argv[1], "r" );
    } else {
        yyin = stdin;
    }
    yylex();
}

int  yywrap() { return 1; }








