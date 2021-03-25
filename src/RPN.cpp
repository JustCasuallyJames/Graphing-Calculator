
#include "../headers/RPN.h"
RPN::RPN() {}
RPN::RPN(Queue<Token*> postfix, double var){
    _answer = rpn(postfix, var);
}
double RPN::operator()(const Queue<Token*>& postfix, const double& x) {
    return rpn(postfix, x);
}
//plot deallocate original queue
double RPN::rpn(Queue<Token*> postfix, double var){
    Stack<Token*> results;
    while(!postfix.isEmpty()){
        Token* value = postfix.pop();
        switch(value->getType()){
            case mathSymbols::Number:
                results.push(new Number(static_cast<Number*>(value)->num()));
                break;
            case mathSymbols::Operator: {
                Token* b = results.pop(); //this would be the 5 instead of 3
                Token* a = results.pop(); //this would be the 3 instead of 5 cuz you're popping from the top
                double bNum = static_cast<Number*>(b)->num();
                double aNum = static_cast<Number*>(a)->num();
                if (static_cast<Operator *>(value)->get_operator() == "+") {
                    //adds the two values together and pushes it to the results stack
                    double answer = bNum + aNum;
                    results.push(new Number(answer));
                } else if (static_cast<Operator *>(value)->get_operator() == "-") {
                    //subtracts the 2nd pop - 1st pop and then pushes it into the results stack
                    double answer = bNum - aNum;

                    results.push(new Number(answer));
                } else if (static_cast<Operator *>(value)->get_operator() == "*") {
                    //multiplies the two popped values together and pushes it to the results stack
                    double answer = aNum * bNum;
                    results.push(new Number(answer));
                } else if (static_cast<Operator *>(value)->get_operator() == "/") {
                    if (isZero(bNum)) {
                        results.push(new Number(0)); //return a nanf (float) or nanl (long double)
                    }else {
                        double answer = aNum / bNum;
                        results.push(new Number(answer));
                    }
                } else if (static_cast<Operator *>(value)->get_operator() == "^") {
                    double answer = pow(aNum, bNum);
                    results.push(new Number(answer));
                }
                delete b;
                delete a;
                break;
            }case mathSymbols::Variable:{
                //pushes the number if it's a variable
                results.push(new Number(var));
                break;
            }
            case mathSymbols::Function:{
                //do functions that only pop once
                //sin, cos, tan, e, ln
                //pop, get the number, push into the stack a number of sin,cos,tan
                Function* func = static_cast<Function*>(value);
                int arguments = func->get_arguments();
                if (arguments == 1) {
                    if (func->get_operator() == "e") { //checks if it's an e
                        if (postfix.isEmpty()) { //checks if it's just an e and not e ^ x
                            results.push(new Number(EULER)); //pushes in the EULER number
                            Token* final = results.pop();
                            return static_cast<Number*>(final)->num();
                        }
                        else { //if it's not empty, it still pushes in the EULER number
                            results.push(new Number(EULER)); 
                        }
                    }
                    else {
                        Token* val = results.pop();
                        //func evaluates(double x) returns a double which is casted to a Number object to be pushed into results
                        results.push(new Number(func->evaluate(static_cast<Number*>(val)->num())));
                        delete val;
                    }
                }
                else if (arguments == 2) {
                    Token* val1 = results.pop(); //pops two values
                    Token* val2 = results.pop();
                    //func evaluates(double x, double y) returns a double which is casted to a Number object to be pushed into results
                    results.push(new Number(func->evaluate(static_cast<Number*>(val2)->num(),static_cast<Number*>(val1)->num())));
                    delete val1; //needed so that there are no memory leaks
                    delete val2; //needed so that there are no memory leaks
                }
                break;
            }
        }
    }
    Token* final = results.pop();
    double finalNum = static_cast<Number*>(final)->num();
    delete final; //deleted is needed so there are no memory leaks
    return finalNum;
}
double RPN::answer(){
    return _answer;
}

bool RPN::isZero(double value) {
    return value >= DBL_MIN && value <= 0;
}
