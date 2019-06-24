#include "stackEval.h"



int stackEval::priority(char op) {

	switch (op) {
	case '^': return 3;
	case '*':
	case '%':
	case '/': return 2;
	case '+':
	case '-': return 1;
	case ')':
	case ']': return -1;
	default: return 0;
	}
}



string stackEval::convert(string in) {
	stack<char> Vstack;
	string posf = "";
	for (int i = 0; i < in.size(); i++) {
		switch (in[i]) {
		case '(':
			Vstack.push('(');
			break;
		case ')':
			while (!Vstack.empty() && Vstack.top() != '(') {
				posf += string(1, Vstack.top()) + " ";
				Vstack.pop();
			}
			Vstack.pop();
			break;
		case '+':
		case '-':
		case '*':
		case '%':
			while (!Vstack.empty() && priority(in[i]) <= priority(Vstack.top())) {
				posf += string(1, Vstack.top()) + " ";
				Vstack.pop();
			}
			Vstack.push(in[i]);
			break;
		case '/':
		case '^':
			while (!Vstack.empty() && priority(in[i]) <= priority(Vstack.top())) {
				posf += string(1, Vstack.top()) + " ";
				Vstack.pop();
			}
			Vstack.push(in[i]);
			break;
		default:
			while (isdigit(in[i]) || in[i] == '.')
				posf += string(1, in[i++]);
			posf += " ";
			i--;
		}
	}
	while (!Vstack.empty()) {
		posf += string(1, Vstack.top()) + " ";
		Vstack.pop();
	}
	return posf;
}

bool stackEval::validateExpressions(string str) {

	regex Vdigit("[-+]?([0-9]*\\.[0-9]+|[0-9]+)");//c++11
	regex Voperator("[\\-\\+\\/\\*\\%\\[\\^]");//c+11
	regex Voperation("^[\\-\\(\\[\\+]?([0-9]*\\.[0-9]+|[0-9]+)+[\\]\\)]*([-+*/^%]+[\\-\\(\\[\\+]?([0-9]*\\.[0-9]+|[0-9]+)+[\\]\\)]*)*$");//c++11

	auto firstParenthesis = 0, lastParethesis = 0, firstBracket = 0, lastBracket = 0;//c++11

	string withoutDigits = "+-/%^*";

	if (regex_match(str, Voperation)) {//c++11
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '(') {
				firstParenthesis = firstParenthesis + 1;
			}
		}
		for (int j = 0; j < str.size(); ++j) {
			if (str[j] == ')')
				lastParethesis = lastParethesis + 1;
		}
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '[') {
				firstBracket = firstBracket + 1;
			}
		}
		for (int j = 0; j < str.size(); ++j) {
			if (str[j] == ']')
				lastBracket = lastBracket + 1;
		}

		if (firstParenthesis == lastParethesis && (firstBracket == lastBracket)) {
			for (int o = 0; o <= withoutDigits.size(); ++o) {
				for (int a = 0; a <= str.size(); ++a) {
					if (str[a] == withoutDigits[o]) {
						for (int h = 0; h <= withoutDigits.size(); ++h) {
							if (str[a - 1] == withoutDigits[h] | str[a + 1] == withoutDigits[h]) { //c++ 14
								cout << "ERROR: INFIX INCORRECT" << endl;
								return false;
							}
							else {
								return true;
							}
						}
					}
				}
			}
		}
	}
	else {
		cout << "ERROR: Don't understand statement" << endl;
	}
	return false;
}


double stackEval::evaluate(string p) {
	stack<double> Vstack;
	double op1, op2;
	for (int i = 0; i < p.size(); i += 2) {
		switch (p[i]) {
		case '^':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(pow(op1, op2));
			break;
		case '*':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(op1 * op2);
			break;
		case '%':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(fmod(op1, op2));
			break;
		case '/':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(op1 / op2);
			break;
		case '+':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(op1 + op2);
			break;
		case '-':
			op2 = Vstack.top(); Vstack.pop();
			op1 = Vstack.top(); Vstack.pop();
			Vstack.push(op1 - op2);
			break;
		default:
			string aux = "";
			while (p[i] != ' ')
				aux += string(1, p[i++]);
			Vstack.push(atof(aux.c_str()));
			i--;
		}
	}
	return Vstack.top();
}