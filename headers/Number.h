//
// Created by james on 5/14/2020.
//

#ifndef TOKEN_NUMBER_H
#define TOKEN_NUMBER_H

#include "constants.h"
#include "Token.h"
using namespace std;

class Number: public Token {
public:
    Number(double num);
    mathSymbols getType() const;
    ostream& print(ostream& outs) const;
    double num() const;
    friend ostream& operator <<(ostream& outs, const Number& t){
        t.print(outs);
        return outs;
    }
    friend ostream& operator <<(ostream& outs, const Number* t){
        t->print(outs);
        return outs;
    }
private:
    double _num;
};


#endif //TOKEN_NUMBER_H
