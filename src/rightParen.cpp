

#include "../headers/rightParen.h"
rightParen::rightParen():Token(){}

mathSymbols rightParen::getType() const{
    return mathSymbols::rightParen;
}
ostream& rightParen::print(ostream& outs) const{
    outs << ")";
    return outs;
}