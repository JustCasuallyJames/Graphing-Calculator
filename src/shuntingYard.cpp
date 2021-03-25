

#include "../headers/shuntingYard.h"
shuntingYard::shuntingYard(const Queue<Token*>& infix){//calls the create_PostFix function
    //create_Postfix
    _postfix = create_postfix(infix);
}
Queue<Token*> shuntingYard::postfix() const{
    return _postfix;
}
Queue<Token*> shuntingYard::create_postfix(Queue<Token*> infix){
    Queue<Token*> results;
    Stack<Token*> operators;
    while(infix.size() > 0){ //if the infix queue is not empty
        Token* value = infix.pop(); //Save the value of the popped value from the infix
        switch(value->getType()){ //check what type the value is, whether it would be number, operation, ( or )
            case mathSymbols::Variable:
            case mathSymbols::Number: //if it's a number
                results.push(value); //just push into the results queue
                break;
            case mathSymbols::Function:
            case mathSymbols::Operator: //if its operators, it's going to get complicated
                if(operators.isEmpty()){ //check if it's empty
                    operators.push(value); //if it is, push a value to it
                }else if((static_cast<Operator*>(*operators.begin()))->get_precedence() == 3){ //special case for exponent ^
                    operators.push(value); //just push to operators stack
                }else if((static_cast<Operator*>(*operators.begin()))->get_precedence() >= static_cast<Operator*>(value)->get_precedence()){
                    //if the operator in stack has a higher precedence
                    //then pop and save the value
                    //push the value
                    //push the lower precedence operator to the operators stack
                    Token* symbol = operators.pop();
                    results.push(symbol);
                    operators.push(value);
                }else{ //safeguard
                    //just push if it's any of the other conditions
                    operators.push(value);
                }
                break;
            case mathSymbols::leftParen:
                operators.push(value); //push into the operators stack
                break;
            case mathSymbols::rightParen:
                //pop from the stack until (
                while((*operators.begin())->getType() != mathSymbols::leftParen){ //check if this NOT (
                    //Pop all the values and push them to results until you see a (
                    Token* temp = operators.pop();
                    results.push(temp);
                }
                //pop the remaining (
                operators.pop();
                break;
            case mathSymbols::Token:
                break;
        }
    }//will return false when it reaches the end
    while(operators.size() > 0){ //if there are leftovers in the operators stack
        Token* temp = operators.pop(); //pop and push them all
        results.push(temp);
    }
    return results;
}