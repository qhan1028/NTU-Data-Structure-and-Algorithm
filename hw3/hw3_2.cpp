#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <cmath>
#include "hw3_2.h"
using namespace std;

class EQUATION {
public:
	double element;
	int isFunction;
};

class DATA {
public:
	DATA();
	~DATA();

	void Read();
	void Infix();
	void Postfix();
	void Execute();

	char *input;
	int input_size;
	double result;
	vector<EQUATION> postfix;
	vector<EQUATION> infix;
};

DATA::DATA() { input = new char[MAX];}

DATA::~DATA() { delete [] input;}

void DATA::Read()
{
	fgets(input, MAX, stdin);
	input_size = strlen(input);
}

bool isNumber(char input) {return (input >= '0' && input <= '9') || input == '.';}

bool isOperat(char input) 
{
	char function[12] = {'+', '-', '*', 's', 'c', 'e', 'l', 'p', 'f', '(', ')', ','};
	for (int i = 0 ; i < 12 ; i++) if (input == function[i]) return true;
	return false;
}

double translate(char input[], int& pos, int preNum, vector<EQUATION> infix, int infix_pos)
{
	char function[5] = {'s','c','e','l','p'};
	double function_num[5] = {SIN, COS, EXP, LOG, POW};
	if (input[pos] == '+' || input[pos] == '-') { //unary + -
		if (infix_pos >= 0 && (infix[infix_pos].element == P_R || (infix[infix_pos].isFunction == 0))) 
			return (input[pos] == '+')? ADD : SUB;
		else return (input[pos] == '+')? U_ADD : U_SUB;
	} else if (input[pos] == 's' && input[pos+1] == 'q') { //sqrt
		pos += 3;
		return SQRT;
	} else if (input[pos] == 'f') { //fabs
		pos += 3;
		return FABS;
	} else if (input[pos] == '(' || input[pos] == ')' || input[pos] == '*') { //parenthesis and  mul
		if (input[pos] == '(') return P_L;
		if (input[pos] == ')') return P_R;
		if (input[pos] == '*') return MUL;
	} else { // sin cos log exp pow
		for (int i = 0 ; i < 5 ; i++) {
			if (input[pos] == function[i]) {
				pos += 2;
				return function_num[i];
			}
		}
	}
	cout << "translate error\n"; 
	return -1;
}

void printFunc(double input)
{
	double function[14] = {ADD, SUB, MUL, U_ADD, U_SUB, SIN, COS, EXP, LOG, POW, SQRT, FABS, P_L, P_R};
	char output[14][6] = {"+ ", "- ", "* ", "+ ", "- ", "sin ", "cos ", "exp ", "log ", "pow ", "sqrt ", "fabs ", "( ", ") "}; 
	for (int i = 0 ; i < 14 ; i++) if (input == function[i]) cout << output[i];
}

void DATA::Infix()
{
	double tmp_num = 0;
	int frac_count = 0;
	int preNum = 0;
	int fraction = 0;
	for (int pos = 0 ; pos <= input_size ; pos++) {
		if (input[pos] == ' ') continue; //ignore spaces
		if (pos == input_size && preNum) { //last number
			EQUATION in;
			for (int i = 0 ; i < frac_count ; i++) tmp_num /= 10;
			in.element = tmp_num;
			in.isFunction = 0;
			infix.push_back(in); break;
		}
		if (isNumber(input[pos])) { //numbers have many digits and fractions
			if (input[pos] == '.') {
				fraction = 1;
				continue;
			} else if (fraction) {
				tmp_num = tmp_num*10 + input[pos] - '0';
				frac_count++;
				preNum = 1; continue;
			} else {
				tmp_num = tmp_num*10 + input[pos] - '0';
				preNum = 1; continue;
			}
		} else if (isOperat(input[pos])) {
			EQUATION in;
			if (preNum) { //first process numbers
				for (int i = 0 ; i < frac_count ; i++) tmp_num /= 10;
				in.element = tmp_num;
				in.isFunction = 0;
				infix.push_back(in);
			} 
			in.isFunction = 1;
			if (input[pos] == ',') {
				in.element = P_R;
				infix.push_back(in);
				in.element = P_L;
				infix.push_back(in);
			} else {
				in.element = translate(input, pos, preNum, infix, infix.size()-1);
				infix.push_back(in);
			}
			frac_count = fraction = preNum = tmp_num = 0;
		} 
	}
}

bool TopIsBigger(double input, double top)
{
	if (top == P_L) return false; //force the operand behind the P_L push into the stack
	else if ((top == U_ADD || top == U_SUB) && (input == U_ADD || input == U_SUB)) return false;
	else return ((int)top/10-(int)input/10 >= 0)? true : false;
}

void DATA::Postfix()
{
	stack<double> operators;
	for (int pos = 0 ; pos <= infix.size() ; pos++) {
		while (pos == infix.size() && !operators.empty()) {//end
			EQUATION post;
			post.element = operators.top();
			post.isFunction = 1;
			postfix.push_back(post);
			operators.pop();
			printf("pop ");
			printFunc(post.element);
			printf("from the stack\n");
			printf("push back ");
			printFunc(post.element);
			printf("to the postfix\n");
		}
		if (!infix[pos].isFunction && pos != infix.size()) { //numbers
			postfix.push_back(infix[pos]);
			printf("push back %f to the postfix\n", infix[pos].element);
		}
		else if (infix[pos].isFunction) { //operators
			EQUATION post;
			post.isFunction = 1;
			if (infix[pos].element == P_L) { //left parantheses
				operators.push(P_L);
				printf("push ");
				printFunc(infix[pos].element);
				printf("to the stack\n");
			} else if (infix[pos].element == P_R) { //right parantheses
				while (operators.top() != P_L) {
					post.element = operators.top();
					postfix.push_back(post);
					operators.pop();
					printf("pop ");
					printFunc(post.element);
					printf("from the stack\n");
					printf("push back ");
					printFunc(post.element);
					printf("to the postfix\n");
				}
				printf("pop ");
				printFunc(operators.top());
				printf("from the stack\n");
				operators.pop(); //pop out the left parantheses
			} else { //normal operators
				while (!operators.empty() && TopIsBigger(infix[pos].element, operators.top())) { //if top is bigger or the same, pop out top
					//beware : P_L is smaller than everyone
					post.element = operators.top();
					postfix.push_back(post);
					operators.pop();
					printf("pop ");
					printFunc(post.element);
					printf("from the stack\n");
					printf("push back ");
					printFunc(post.element);
					printf("to the postfix\n");
				}
				operators.push(infix[pos].element);
				printf("push ");
				printFunc(infix[pos].element);
				printf("to the stack\n");
			}
		}
	}
	cout << "Postfix Exp: ";
	for (int pos = 0 ; pos < postfix.size() ; pos++) {
		if (!postfix[pos].isFunction && pos != postfix.size()-1) printf("%f ", postfix[pos].element);
		else printFunc(postfix[pos].element);
	}
	cout << "\n";
}

double Calculate1(double value1, double operat, double value2)
{
	switch ((int)operat) {
		case ADD : return (value1 + value2);
		case SUB : return (value1 - value2);
		case MUL : return (value1 * value2);
		case POW : return pow(value1, value2);
		default : cout << "Calculate1 error\n";
	}
	return -1;
}

double Calculate2(double value, double operat)
{
	switch ((int)operat) {
		case U_ADD : return +(value);
		case U_SUB : return -(value);
		case SIN : return sin(value);
		case COS : return cos(value);
		case EXP : return exp(value);
		case LOG : return log(value);
		case SQRT : return sqrt(value);
		case FABS : return fabs(value);
		default : cout << "Calculate2 error\n";
	}
	return -1;
}

void DATA::Execute()
{
	stack<double> number;
	double value1, value2;

	for (int pos = 0 ; pos < postfix.size() ; pos++) {
		EQUATION now = postfix[pos];
		if (!now.isFunction) {
			number.push(now.element);
			if (postfix.size() == 1) result = now.element;
		} else if (now.isFunction) {
			if (now.element == ADD || now.element == SUB || now.element == MUL || now.element == POW) {
				value2 = number.top(); number.pop();
				value1 = number.top(); number.pop();
				result = Calculate1(value1, now.element, value2);
				number.push(result);
			} else {
				value1 = number.top(); number.pop();
				result = Calculate2(value1, now.element);
				number.push(result);
			}
		} 
	}
	printf("RESULT: %f\n", result);
}

int main()
{
	while(cin.peek() != EOF) {
		DATA data;
		data.Read();
		data.Infix();
		data.Postfix();
		data.Execute();
	}
	return 0;
}