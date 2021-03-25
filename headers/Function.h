#ifndef SHUNTINGYARD_FUNCTION_H
#define SHUNTINGYARD_FUNCTION_H
#include "Operator.h"
#include <string>
class Function: public Operator{
public:
    Function(string equation);
    mathSymbols getType() const;
    int get_arguments();
    double evaluate(double value);
    double evaluate(double value1, double value2);
    ostream& print(ostream& outs);
private:
    int _arguments;
    double _answer;
};
#endif //SHUNTINGYARD_FUNCTION_H
