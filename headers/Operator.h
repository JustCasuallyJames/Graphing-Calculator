//
// Created by james on 5/14/2020.
//

#ifndef TOKEN_OPERATOR_H
#define TOKEN_OPERATOR_H

#include <cassert>
#include "Token.h"
using namespace std;
class Operator: public Token{
public:
    Operator(string operation);
    mathSymbols getType() const;
    ostream& print(ostream& outs) const;
    int get_precedence();
    string get_operator();
    friend ostream& operator <<(ostream& outs, const Operator& t){
        t.print(outs);
        return outs;
    }
    friend ostream& operator <<(ostream& outs, const Operator* t){
        t->print(outs);
        return outs;
    }
private:
    string _operation;
    int _precedence; //the hierarchy of the operations (pemdas)
    void set_precedence(string operation);
};


#endif //TOKEN_OPERATOR_H
