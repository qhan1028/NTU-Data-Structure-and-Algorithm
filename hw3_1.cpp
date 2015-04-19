#include <iostream>
#include <cstdio>
#include <stack>
#include <hw3_1.h>
using namespace std;

class POSTFIX {
public:
	int element;
	int isFunction;
};

class DATA {
public:
	DATA();
	~DATA();

	void Read();
	void Postfix();
	void Calculate();

	char *input;
	int input_size;
	
	vector<POSTFIX> postfix;

	int result;
};

DATA::DATA()
{
	input = new char[MAX];
}

DATA::~DATA()
{
	delete [] input;
}

void DATA::Read()
{
	cin.getline(input, MAX);
	input_size = cin.gcount();
}

bool isNumber(char input) {return (input >= '0' && input <= '9');}

bool isOperand(char input) 
{
	return (input == '+' || input == '-' || 
		input == '*' || input == '/' || input == '%');
}

bool TopIsBigger(char input, char top)
{
	if (top == '*' || top == '/' || top == '%') return true;
	else if (top == '+' || top == '-' ) {
		if (input == '*' || input == '/' || input == '%') return false;
		else return true;
	} else return false;
}

int translate(char input)
{
	switch(input) {
		case:'+' return ADD;
		case:'-' return SUB;
		case:'*' return MUL;
		case:'/' return DIV;
		case:'%' return MOD;
		default: 
		cout << "operator translation error\n";
		return -1;
	}
}

void DATA::Postfix()
{
	queue<int> digit;
	stack<char> operators;
	int pos = 0;
	int preNum = 0;

	for (pos = 0 ; pos <= input_size ; pos++) {
		if (pos == input_size) {
			if (preNum) {
				POSTFIX post;
				int tmp_num = 0;
				while (!digit.empty()) {
					tmp_num = 10*tmp_num + digit.pop_front();
				}
				post.element = tmp_num;
				post.isFunction = 0;
				postfix.push_back(post);
				preNum = 0;
			}
			while (!operators.empty()) {
				POSTFIX tmp_post;
				post.element = translate(operators.pop());
				post.isFunction = 1;
				postfix.push_back(post);
			}
			break;
		}
		if (isNumber(input[pos])) {
			digit.push_back(input[pos]-'0');
			preNum = 1;
			continue;
		}
		if (isOperand(input[pos])) {
			if (preNum) {
				POSTFIX post;
				int tmp_num = 0;
				while (!digit.empty()) {
					tmp_num = 10*tmp_num + digit.pop_front();
				}
				post.element = tmp_num;
				post.isFunction = 0;
				postfix.push_back(post);
				preNum = 0;
			}
			while (TopIsBigger(input[pos], operators.top())) {
				POSTFIX tmp_post;
				post.element = translate(operators.pop());
				post.isFunction = 1;
				postfix.push_back(post);
			}
			operators.push(input[pos]);
		}
	}
}

int main()
{
	do {
		DATA data;
		data.Read();
		data.Postfix();
		data.Calculate();
	} while(cin.peek() != EOF);

	return 0;
}