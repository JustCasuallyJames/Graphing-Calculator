

#ifndef SHUNTINGYARD_LEFTPAREN_H
#define SHUNTINGYARD_LEFTPAREN_H


#include "Token.h"

class leftParen : public Token{
public:
    leftParen();
    mathSymbols getType() const;
    ostream& print(ostream& outs) const;
private:
    string _lparen;
};


#endif //SHUNTINGYARD_LEFTPAREN_H
