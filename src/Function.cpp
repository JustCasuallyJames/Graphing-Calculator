#include "../headers/Function.h"
Function::Function(string equation): Operator(equation){
    if(equation == "sin" || equation == "cos" || equation == "tan" || equation == "ln"|| equation == "e"){
        _arguments = 1;
    }else if(equation == "log"){
        _arguments = 2;
    }
}
int Function::get_arguments(){
    return _arguments;
}
double Function::evaluate(double value) {
    string equation = Operator::get_operator();
    if (equation == "sin") {
        return sin(value);
    }
    else if (equation == "cos") {
        return cos(value);
    }
    else if (equation == "tan") {
        return tan(value);
    }
    else if (equation == "ln") { //natural log
        return log(value);
    }
    else if (equation == "e") {
        return exp(value);
    }
}

double Function::evaluate(double value1, double value2) {
    string equation = Operator::get_operator();
    if (equation == "log") {
        return log(value2) / log(value1);
    }
}

mathSymbols Function::getType() const {
    return mathSymbols::Function;
}
