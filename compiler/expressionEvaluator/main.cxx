#include "header.h"
#include <vector>
#include <iostream>

extern FILE *yyin;
extern int yyparse ();
extern int yydebug;

std::vector<id *> varArray;
expr *E = NULL;

char* strdup(char *src)
{
    int len = strlen(src);
    char *retStr = (char*) malloc((len + 1)*sizeof(char));
    strcpy(retStr, src);
    return retStr;
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        yyin = fopen( argv[1], "r" );
    } else {
        yyin = stdin;
    }

    yyparse();

    std::cout << "Calculated value = " << E->evaluate() << std::endl;

    return 0;
}

void actionFunction1(char *name, int value)
{
    id *ident = new id(name, value);
    varArray.push_back(ident);
}

expr *actionFunction2(int value)
{
    return new num(value);
}

expr *actionFunction3(char *name)
{
    for (std::vector<id *>::iterator it = varArray.begin(); it != varArray.end() ; ++it)
    {
        if (strcmp((*it)->getName(), name) == 0) {
            return *it;
        }
    }
    return NULL;
}

expr *actionFunction4(expr *lhs, expr *rhs, opType op)
{
    return new binExpr(lhs, rhs, op);
}




















