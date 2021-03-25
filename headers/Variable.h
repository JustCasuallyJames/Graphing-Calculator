
#ifndef SHUNTINGYARD_VARIABLE_H
#define SHUNTINGYARD_VARIABLE_H
#include "Token.h"
class Variable: public Token{
public:
    Variable();
    mathSymbols getType() const;
    ostream& print(ostream& outs) const;
    friend ostream& operator <<(ostream& outs, const Variable& v){
        v.print(outs);
        return outs;
    }
    friend ostream& operator <<(ostream& outs, const Variable* v){
        v->print(outs);
        return outs;
    }
};




#endif //SHUNTINGYARD_VARIABLE_H
