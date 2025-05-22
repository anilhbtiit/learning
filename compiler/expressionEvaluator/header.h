#ifndef _HEADER_
#define _HEADER_ 1

#include <cstdlib>
#include <cstdio>
#include <cstring>

char* strdup(char *);

typedef enum 
{
    op_plus,
    op_minus,
    op_multiply,
    op_divide
} opType;

class expr
{
    public:
        expr() {}
        virtual int evaluate() { return 0; }
};

class id : public expr
{
    char *_name;
    int   _value;
    public:
        id(char *name, int value):
            _name(name), _value(value) {}
        char *getName() {
            return _name;
        }
        int evaluate() {
            return _value;
        }
};

class num : public expr
{
    int _value;
    public:
        num(int value) : _value(value) {}
        int evaluate() {
            return _value;
        }
};

class binExpr : public expr
{
    expr  *_lhs;
    expr  *_rhs;
    opType _op;
    public:
        binExpr(expr *lhs, expr *rhs, opType op):
            _lhs(lhs), _rhs(rhs), _op(op) {}
        int evaluate() {
            switch(_op) {
                case op_plus:
                    return _lhs->evaluate() + _rhs->evaluate();
                case op_minus:
                    return _lhs->evaluate() - _rhs->evaluate();
                case op_multiply:
                    return _lhs->evaluate() * _rhs->evaluate();
                case op_divide:
                    return _lhs->evaluate() / _rhs->evaluate();
            } 
            return -1;
        }
};

void  actionFunction1(char *name, int value);
expr *actionFunction2(int value);
expr *actionFunction3(char *name);
expr *actionFunction4(expr *lhs, expr *rhs, opType op);

#endif
