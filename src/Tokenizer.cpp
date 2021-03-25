#define _CRT_SECURE_NO_WARNINGS
#include "../headers/Tokenizer.h"
Tokenizer::Tokenizer() {

}
Queue<Token*> Tokenizer::Tokenize(const string equation) {
	//stringstream ss;
	Queue<Token*> results;

	stringstream ss(equation);
	string token;
	//isdigit(int c) goes by the ascii value of the integer
	while (getline(ss, token, ' ')) {
		if (token[0] == 'x' || token[0] == 'X') {
			results.push(new Variable());
		}
		else if (isalpha(token[0])) { 
			results.push(new Function(token));
			//if starts with a character other than x, then its automatically function
		}
		else if (isdigit(token[0])) {
			//if the first value is a number, it's automatically pushed
			results.push(new Number(stod(token)));
		}
		else if (isOperator(token)) {
			//using internal isOperator function, checks if it's an operator
			results.push(new Operator(token));
		}
		else if (token == "(") {
			//checks if it's a left parenthesis
			results.push(new leftParen());
		}
		else if (token == ")") {
			//checks if it's a right parenthesis
			results.push(new rightParen());
		}
	}
	return results;
}
Queue<Token*> Tokenizer::operator()(const string equation)
{
	return Tokenize(equation);
}
/*
	Internal Function isOperator returns true if it's one of the arimethic operators
	+,-,/,*
	Params: the operator as a string
*/
bool Tokenizer::isOperator(string op) {
	return op == "+" || op == "-" || op == "*" || op == "/" || op == "^";
}