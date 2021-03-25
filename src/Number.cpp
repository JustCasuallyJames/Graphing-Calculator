#include "../headers/Number.h"

Number::Number(double num):Token(){
    _num = num;
}
mathSymbols Number::getType() const{
    return mathSymbols::Number;
}
ostream& Number::print(ostream& outs) const{
    outs << _num;
    return outs;
}
double Number::num() const{
    return _num;
}