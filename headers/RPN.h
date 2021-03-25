//
// Created by james on 5/26/2020.
//

#ifndef SHUNTINGYARD_RPN_H
#define SHUNTINGYARD_RPN_H

#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include "Number.h"
#include "Operator.h"
#include "Function.h"
#include <cmath>
class RPN {
public:
    RPN();
    RPN(Queue<Token*> postfix, double var=0);
    double rpn(Queue<Token*> postfix, double var);
    double answer();
    double operator()(const Queue<Token*>& postfix, const double& x);
private:
    bool isZero(double value);
    double _answer;
};


#endif //SHUNTINGYARD_RPN_H
