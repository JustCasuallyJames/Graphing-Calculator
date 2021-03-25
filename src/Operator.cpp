//
// Created by james on 5/14/2020.
//

#include "../headers/Operator.h"

Operator::Operator(string operation){
    _operation = operation;
    set_precedence(operation);
}
mathSymbols Operator::getType() const{
    return mathSymbols::Operator;
}
ostream& Operator::print(ostream& outs) const{
    outs << _operation;
    return outs;
}
void Operator::set_precedence(string operation){
    if(operation == "+" || operation == "-"){
        _precedence = 1;
    }else if(operation == "*" || operation == "/"){
        _precedence = 2;
    }else if(operation == "^"){
        _precedence = 3;
    }else{
        _precedence = 100;
    }
}
int Operator::get_precedence(){
    return _precedence;
}
string Operator::get_operator(){
    return _operation;
}