#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include "hw3_1.h"
using namespace std;

class EQUATION {
public:
	int element;
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
	
	vector<EQUATION> postfix;
	vector<EQUATION> infix;

	int result;
};

DATA::DATA() { input = new char[MAX];}

DATA::~DATA() { delete [] input;}

void DATA::Read()
{
	cin.getline(input, MAX);
	input_size = cin.gcount();
}

bool isNumber(char input) {return (input >= '0' && input <= '9');}

bool isOperand(char input) 
{
	char operand[14] = {'+', '-', '*', '/', '%', '&', '^', '|', '<', '>', '(', ')', '~', '!'};
	for (int i = 0 ; i <= 13 ; i++) {
		if (input == operand[i]) return true;
	}
	return false;
}

int translate1(char input)
{
	switch(input) {
		case'<': return B_LS;
		case'>': return B_RS;
		case'&': return L_AND;
		case'|': return L_OR;
		default: 
		cout << "operator translation error\n";
		return -1;
	}
}

int translate2(char input)
{
	switch(input) {
		case'+': return ADD;
		case'-': return SUB;
		case'*': return MUL;
		case'/': return DIV;
		case'%': return MOD;
		case'&': return B_AND;
		case'^': return B_XOR;
		case'|': return B_OR;
		case'(': return P_L;
		case')': return P_R;
		case'~': return B_NOT;
		case'!': return L_NOT;
		default: 
		cout << "operator translation error\n";
		return -1;
	}
}

void DATA::Infix()
{
	int isNegetive = 0;
	int tmp_num = 0;
	int preNum = 0;
	for (int pos = 0 ; pos < input_size ; pos++) {
		if (input[pos] == '\n' && preNum) { //last number
			EQUATION in;
			in.element = (isNegetive)? (-1)*tmp_num : tmp_num;
			in.isFunction = 0;
			infix.push_back(in);
		}
		if (input[pos] == ' ') continue; //ignore spaces
		if (isNumber(input[pos])) { //numbers have many digits
			tmp_num = tmp_num*10 + input[pos]- '0';
			preNum = 1;
			continue;
		}
		if (isOperand(input[pos])) {
			if (preNum) { //first process numbers
				EQUATION in;
				in.element = (isNegetive)? (-1)*tmp_num : tmp_num;
				in.isFunction = 0;
				infix.push_back(in);
				isNegetive = preNum = 0;
			
				if (input[pos] == input[pos+1]) {
					in.element = translate1(input[pos]);
					in.isFunction = 1;
					infix.push_back(in);
					pos++; //because these operators need two chars
				} else {
					in.element = translate2(input[pos]);
					in.isFunction = 1;
					infix.push_back(in);
				}
			} else { //unary + -
				if (input[pos] == '-') isNegetive = 1;
				if (input[pos] == '+') isNegetive = 0;
			}
		}
	}
}

bool TopIsBigger(int input, int top)
{
	if (top == P_L) return false; //force the operand behind the P_L push into the stack
	else return (top/10-input/10 >= 0)? true : false;
}

void DATA::Postfix()
{
	stack<int> operators;
	int parantheses = 0;
	for (int pos = 0 ; pos <= infix.size() ; pos++) {
		if (pos == infix.size()) { //end
			while (!operators.empty()) {
				EQUATION post;
				post.element = operators.top();
				post.isFunction = 1;
				postfix.push_back(post);
				operators.pop();
			}
			break;
		}
		if (!infix[pos].isFunction) { //numbers
			postfix.push_back(infix[pos]);
		}
		else if (infix[pos].isFunction) { //operators
			if (infix[pos].element == P_L) { //left parantheses
				operators.push(P_L);
			} else if (infix[pos].element == P_R) { //right parantheses
				while (operators.top() != P_L) {
					EQUATION post;
					post.element = operators.top();
					post.isFunction = 1;
					postfix.push_back(post);
					operators.pop();
				}
				operators.pop(); //pop out the left parantheses
			} else { //normal operators
				while (TopIsBigger(infix[pos].element, operators.top())) { //if top is bigger or the same, pop out top
					//beware : P_L is smaller than everyone
					EQUATION post;
					post.element = operators.top();
					post.isFunction = 1;
					postfix.push_back(post);
					operators.pop();
				}
				operators.push(infix[pos].element);
			}
		}
	}
}

int Calculate(int value1, int operat, int value2)
{
	switch (operat) {
		case ADD : return (value1 + value2);
		case SUB : return (value1 - value2);
		case MUL : return (value1 * value2);
		case DIV : return (value1 / value2);
		case MOD : return (value1 % value2);
		case B_AND : return (value1 & value2);
		case B_OR : return (value1 | value2);
		case B_XOR : return (value1 ^ value2);
		case B_LS : return (value1 << value2);
		case B_RS : return (value1 >> value2);
		case L_AND : return (value1 && value2);
		case L_OR : return (value1 || value2);
	}
}

void DATA::Execute()
{
	stack<int> number;
	stack<int> operators;
	int value1;
	int value2;

	for (int pos = 0 ; pos < postfix.size() ; pos++) {
		if (!postfix[pos].isFunction) {
			number.push(postfix[pos].element);
		} else if (postfix[pos].isFunction) {
			if 
			value2 = number.top(); number.pop();
			value1 = number.top(); number.pop();
			result = Calculate(value1, postfix[pos].element, value2);
			number.push(result);
		} 
	}
	#ifdef ANSWER
	printf("%d\n", result);
	#endif
}

int main()
{
	do {
		DATA data;
		data.Read();
		data.Infix();
		data.Postfix();
		data.Execute();
	} while(cin.peek() != EOF);
	return 0;
}