#include "../headers/Variable.h"

Variable::Variable(){}
mathSymbols Variable::getType() const{
    return mathSymbols::Variable;
}
ostream& Variable::print(ostream& outs) const{
    outs << "x";
    return outs;
}