#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class stackEval
{
public:
	//--------------------------Functions
	inline static int priority(char); //c++ 17 declarar e inicializar variables miembro en un solo lugar,mejora para aumentar el tiempo de ejecución de un programa.
	string convert(string);
	double evaluate(string);
	bool validateExpressions(string);



};

