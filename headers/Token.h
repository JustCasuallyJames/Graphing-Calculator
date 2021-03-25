//
// Created by james on 5/14/2020.
//

#ifndef TOKEN_TOKEN_H
#define TOKEN_TOKEN_H
#include <iostream>
#include "Token.h"
enum class mathSymbols {
    Token,
    Number,
    Variable,
    Operator,
    leftParen,
    rightParen,
    Function
};
using namespace std;
class Token {
public:
    Token();
    virtual mathSymbols getType() const;
    virtual ostream& print(ostream& outs) const;
    virtual int get_precedence();
    friend ostream& operator <<(ostream& outs, const Token& t){
        t.print(outs);
        return outs;
    }
    friend ostream& operator <<(ostream& outs, const Token* t){
        t->print(outs);
        return outs;
    }

};


#endif //TOKEN_TOKEN_H
