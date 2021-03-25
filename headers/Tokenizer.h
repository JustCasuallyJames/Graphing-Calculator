#pragma once
#include "Queue.h"
#include "Token.h"
#include "Number.h"
#include "Function.h"
#include "Variable.h"
#include "Operator.h"
#include "leftParen.h"
#include "rightParen.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
class Tokenizer{
public:
	Tokenizer();
	Queue<Token*> Tokenize(const string equation);
	Queue<Token*> operator ()(const string equation);
private:
	bool isOperator(string op);
};

