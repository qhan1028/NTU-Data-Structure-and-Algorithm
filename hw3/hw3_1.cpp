#include <iostream>
#include <cstdio>
#include <cstring>
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
	int result;
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
		cout << "operator translation1 error\n";
		return -1;
	}
}

int translate2(char input)
{
	int function[12] = {ADD, SUB, MUL, DIV, MOD, B_AND, B_XOR, B_OR, B_NOT, L_NOT, P_L, P_R};
	char output[12] = {'+','-','*','/','%','&','^','|','~','!','(',')'}; 
	for (int i = 0 ; i < 18 ; i++) 
		if (input == output[i]) return function[i];
}

int translate3(char input)
{
	switch (input) {
		case '+' : return U_ADD;
		case '-' : return U_SUB;
		default : return -1;
	}
}

void printFunc(int input)
{
	int function[18] = {ADD, SUB, MUL, DIV, MOD, B_AND, B_XOR, B_OR, B_NOT, B_LS, B_RS, L_AND, L_OR, L_NOT, U_ADD, U_SUB, P_L, P_R};
	char output[18][4] = {"+ ", "- ", "* ", "/ ", "% ","& ","^ ","| ","~ ", "<< ", ">> ", "&& ", "|| ", "! ", "+ ", "- ", "( ", ") "}; 
	for (int i = 0 ; i < 18 ; i++) if (input == function[i]) cout << output[i];
}

void DATA::Infix()
{
	int tmp_num = 0;
	int preNum = 0;
	for (int pos = 0 ; pos <= input_size ; pos++) {
		if (pos == input_size && preNum) { //last number
			EQUATION in;
			in.element = tmp_num;
			in.isFunction = 0;
			infix.push_back(in); break;
		}
		if (input[pos] == ' ') continue; //ignore spaces
		if (isNumber(input[pos])) { //numbers have many digits
			tmp_num = tmp_num*10 + input[pos]- '0';
			preNum = 1; continue;
		} else if (isOperand(input[pos])) {
			EQUATION in;
			if (preNum) { //first process numbers
				in.element = tmp_num;
				in.isFunction = 0;
				infix.push_back(in);
			} 
			in.isFunction = 1;
			if (input[pos] == input[pos+1] && input[pos] != '(' && input[pos] != ')' && input[pos] != '+' && input[pos] != '-' && input[pos] != '!' && input[pos] != '~') {
				in.element = translate1(input[pos]);
				infix.push_back(in);
				pos++; //because these operators need two chars
			} else if (input[pos] == '+' || input[pos] == '-') {
				if (pos == 0 || (infix[infix.size()-1].element != P_R && !preNum) ) {
					in.element = translate3(input[pos]);
					infix.push_back(in);
				} else {
					in.element = translate2(input[pos]);
					infix.push_back(in);
				}
			} else {
				in.element = translate2(input[pos]);
				infix.push_back(in);
			}
			preNum = tmp_num = 0;
		} else if (preNum) { //numbers have many digits
			EQUATION in;
			in.element = tmp_num;
			in.isFunction = 0;
			infix.push_back(in);
			preNum = 0; 
		}
	}
}

bool TopIsBigger(int input, int top)
{
	if (top == P_L) return false;//force the operand behind the P_L push into the stack
	else if ((top == U_ADD || top == U_SUB || top == B_NOT || top == L_NOT) && (input == U_ADD || input == U_SUB || input == B_NOT || input == L_NOT)) return false;
	else return (top/10-input/10 >= 0)? true : false;
}

void DATA::Postfix()
{
	stack<int> operators;
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
			printf("push back %d to the postfix\n", infix[pos].element);
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
		if (postfix[pos].isFunction == 0 && pos != postfix.size()-1) cout << postfix[pos].element << " ";
		else printFunc(postfix[pos].element);
	}
	cout << "\n";
}

int Calculate1(int value1, int operat, int value2)
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
		default : cout << "Calculate1 error\n";
	}
	return 0;
}

int Calculate2(int value, int operat)
{
	if (operat == B_NOT) return ~(value);
	if (operat == L_NOT) return !(value);
	if (operat == U_ADD) return +(value);
	if (operat == U_SUB) return -(value);
	else {
		cout << "Calculate2 error\n";
		return 0;
	}
}

void DATA::Execute()
{
	stack<int> number;
	stack<int> operators;
	int value1, value2;

	for (int pos = 0 ; pos < postfix.size() ; pos++) {
		if (!postfix[pos].isFunction) {
			number.push(postfix[pos].element);
			if (postfix.size() == 1) result = postfix[pos].element;
		} else if (postfix[pos].isFunction) {
			if (postfix[pos].element == B_NOT || postfix[pos].element == L_NOT || postfix[pos].element == U_ADD || postfix[pos].element == U_SUB) {
				value1 = number.top(); number.pop();
				result = Calculate2(value1, postfix[pos].element);
				number.push(result);
			} else {
				value2 = number.top(); number.pop();
				value1 = number.top(); number.pop();
				result = Calculate1(value1, postfix[pos].element, value2);
				number.push(result);
			}
		} 
	}
	printf("RESULT: %d\n", result);
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