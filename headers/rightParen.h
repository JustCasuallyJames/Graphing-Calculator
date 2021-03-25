

#ifndef SHUNTINGYARD_RIGHTPAREN_H
#define SHUNTINGYARD_RIGHTPAREN_H


#include "Token.h"

class rightParen : public Token{
public:
    rightParen();
    mathSymbols getType() const;
    ostream& print(ostream& outs) const;
private:
    string _rparen;
};


#endif //SHUNTINGYARD_RIGHTPAREN_H
