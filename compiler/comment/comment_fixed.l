%{
#include <stdio.h>
char str[100];
%}
%x C_COMMENT


%%
"/*"            { str[0] = '\0'; BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { printf("Matched Comment: %s\n", str); BEGIN(INITIAL); }
<C_COMMENT>\n   { strcat(str, yytext); }
<C_COMMENT>.    { strcat(str, yytext); }
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








