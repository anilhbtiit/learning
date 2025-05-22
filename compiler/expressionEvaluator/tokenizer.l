%{
#include "header.h"
#include "parser.tab.h"
%}

letters [a-zA-Z]
idChars [{letter}0-9]
%%

{letters}+{idChars}* { yylval.strVal = strdup(yytext); return IDENT; }
[1-9][0-9]* { yylval.intVal = atoi(yytext); return NUM; }

"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"=" { return ASSIGN; }

[ \t\n] { /* ignore whitespace */ }

. { return UNKNOWN_TOKEN; }


%%

int yywrap()
{
    printf("Scanning Completed.\n");
    return 1;
}



