

#ifndef SHUNTINGYARD_SHUNTINGYARD_H
#define SHUNTINGYARD_SHUNTINGYARD_H


#include "Token.h"
#include "Operator.h"
#include "Number.h"
#include "leftParen.h"
#include "rightParen.h"
#include "Function.h"
#include "Variable.h"
#include "Queue.h"
#include "Stack.h"
class shuntingYard {
public:
    shuntingYard(const Queue<Token*>& infix);//calls the create_PostFix function
    Queue<Token*> postfix() const; //<- getter
    friend ostream& operator<<(ostream& outs, const shuntingYard& sy){
        //do not print out the queue from the queue class
        return outs;
    }
private:
    Queue<Token*> _postfix; //has all the numbers and operations afterwards
    Queue<Token*> create_postfix(Queue<Token*> infix); //Runs the shunting yard algorithm
    //Return the queue<Token*> so that you can set _postfix equal to it.

};


#endif //SHUNTINGYARD_SHUNTINGYARD_H
