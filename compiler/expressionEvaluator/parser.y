%{
#include "header.h"
void yyerror(const char *s);
extern int yylex();
extern expr *E;
%}
%union  {
    char *strVal;
    int   intVal;
    expr *expr_t;
}

%token IDENT
%token NUM
%token ASSIGN
%token ADD
%token SUB
%token MUL
%token DIV
%token UNKNOWN_TOKEN

%left ADD SUB
%left MUL DIV

%type < strVal > IDENT
%type < intVal > NUM
%type < expr_t > expr

%%

problem         : assignment_list expr
{
    printf("Rule: problem         : assignment_list expr");
    printf("\n");
    E = $2;
}

assignment_list : assignment_list assignment
{
    printf("Rule: assignment_list : assignment_list assignment");
    printf("\n");
}
|

assignment      : IDENT ASSIGN NUM
{
    printf("Rule: assignment      : IDENT ASSIGN NUM");
    printf("\n");
    actionFunction1($1, $3);
}

expr            : NUM
{
    printf("Rule: expr            : NUM");
    printf("\n");
    $$ = actionFunction2($1);
}
| IDENT 
{
    printf("Rule: expr            : IDENT");
    printf("\n");
    $$ = actionFunction3($1);
}
| expr ADD expr
{
    printf("Rule: expr            : expr ADD expr");
    printf("\n");
    $$ = actionFunction4($1, $3, op_plus);
}
| expr SUB expr
{
    printf("Rule: expr            : expr SUB expr");
    printf("\n");
    $$ = actionFunction4($1, $3, op_minus);
}
| expr MUL expr
{
    printf("Rule: expr            : expr MUL expr");
    printf("\n");
    $$ = actionFunction4($1, $3, op_multiply);
}
| expr DIV expr
{
    printf("Rule: expr            : expr DIV expr");
    printf("\n");
    $$ = actionFunction4($1, $3, op_divide);
}

%%

void yyerror(const char *s)
{
    printf("%s\n", s);
}




