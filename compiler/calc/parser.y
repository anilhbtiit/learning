%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union { int num; }    // Define YYSTYPE for tokens carrying values

%token <num> NUMBER    // Tokens with values (e.g., numbers)
%token PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN END
%type <num> input expression  // Declare type for non-terminals

%left PLUS MINUS       // Operator precedence (lowest)
%left MULTIPLY DIVIDE  // Operator precedence (higher)
%right UMINUS          // Unary minus precedence

%%

// Start symbol
input:
    expression END { printf("Result: %d\n", $1); }
;

// Expression rules
expression:
    expression PLUS expression     { $$ = $1 + $3; }
  | expression MINUS expression    { $$ = $1 - $3; }
  | expression MULTIPLY expression { $$ = $1 * $3; }
  | expression DIVIDE expression   { 
        if ($3 == 0) { yyerror("Division by zero!"); $$ = 0; }
        else $$ = $1 / $3; 
    }
  | LPAREN expression RPAREN       { $$ = $2; }  // Handle parentheses
  | MINUS expression %prec UMINUS  { $$ = -$2; } // Handle negative numbers
  | NUMBER                         { $$ = $1; }  // Base case: single number
;

%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter an expression (e.g., 3 + 4 * 2):\n");
    yyparse();
    return 0;
}

