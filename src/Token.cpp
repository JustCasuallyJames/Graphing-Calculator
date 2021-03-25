//
// Created by james on 5/14/2020.
//

#include "../headers/Token.h"
Token::Token() {}
mathSymbols Token::getType() const{
    return mathSymbols::Token;
}
ostream& Token::print(ostream& outs) const{
    return outs;
}
int Token::get_precedence(){return 0;}