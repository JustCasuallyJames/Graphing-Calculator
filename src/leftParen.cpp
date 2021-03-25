

#include "../headers/leftParen.h"
leftParen::leftParen():Token(){}
mathSymbols leftParen::getType() const{
    return mathSymbols::leftParen;
}
ostream& leftParen::print(ostream& outs) const{
    outs << "(";
    return outs;
}
