%{
#include "parser.tab.h"
%}

%%

[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MULTIPLY; }
"/"            { return DIVIDE; }
"("            { return LPAREN; }
")"            { return RPAREN; }
";"            { return END; }
[ \t\n]        { /* Ignore spaces, tabs, and newlines */ }
.              { printf("Unexpected character: %s\n", yytext); }

%%
int yywrap() { return 1; }   // Required for Flex compatibility

