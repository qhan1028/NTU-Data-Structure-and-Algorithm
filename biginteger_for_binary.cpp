#include <string>
#include <iostream>
#include "biginteger_for_binary.h"
#define MAXDIGIT 256
using namespace std;

BigInteger::BigInteger() 
{
    digit = new int[MAXDIGIT];
    size = 0;
    for (int i = 0 ; i < MAXDIGIT ; i++) {
    	digit[i] = 0;
    }
}

BigInteger::BigInteger(const int& input)
{
	digit = new int[MAXDIGIT];
	size = 0;
	int tmp = input, mod;
    for (int i = 0 ; i < MAXDIGIT ; i++) {
    	mod = tmp%10;
    	digit[i] = mod;
    	tmp /= 10;
    }
    for (int i = MAXDIGIT-1 ; i >= 0 ; i--) {
		if (digit[i] != 0) {
			size = i+1;
			break;
		}
	}
}

BigInteger::BigInteger(const std::string& input)
{
	digit = new int[MAXDIGIT];
	size = input.length();
	for (int i = 0 ; i < MAXDIGIT ; i++) {
		digit[i] = 0;
	}
	for (int i = size-1, j = 0 ; i >= 0 ; i--, j++) {
		digit[i] = (input[j]-48);
	}
}

BigInteger::BigInteger(const BigInteger& input)
{
	digit = new int[MAXDIGIT];
	size = input.size;
	for (int i = 0 ; i < MAXDIGIT ; i++) 
		digit[i] = input.digit[i];
}

BigInteger::~BigInteger()
{
	delete []digit;
}

bool BigInteger::operator<(const BigInteger& input) const
{
	if (this->size < input.size) return true;
	else if (this->size == input.size) {
		for (int i = this->size - 1 ; i >= 0 ; i--) {
			if (this->digit[i] < input.digit[i]) return true;
			else if (this->digit[i] == input.digit[i]) continue;
			else return false;
		}
	}
	else return false;
}

const BigInteger BigInteger::operator-(const BigInteger& input) const
{
	int excess = 0;
	BigInteger tmp(0);
	for (int i = 0 ; i < MAXDIGIT ; i++) {
		if (this->digit[i] < (input.digit[i] + excess)) {
			tmp.digit[i] = this->digit[i] - input.digit[i] + 10 - excess;
			excess = 1;
		} else {
			tmp.digit[i] = this->digit[i] - input.digit[i] - excess;
			excess = 0;
		}
	}
	for (int i = MAXDIGIT-1 ; i >= 0 ; i--) {
		if (tmp.digit[i] != 0) {
			tmp.size = i+1;
			break;
		}
	}
	return tmp;
}

const BigInteger BigInteger::operator*(const BigInteger& input) const
{
	int excess = 0;
	BigInteger tmp(0);
	int i, j;
	for (i = 0 ; i <= MAXDIGIT-1 ; i++) {
		for (j = 0 ; i+j <= MAXDIGIT-1 ; j++) {
			tmp.digit[i+j] = tmp.digit[i+j] + (this->digit[i]*input.digit[j]);
		}
	}
	excess = 0;
	int temp = 0;
	for (i = 0 ; i < MAXDIGIT ; i++) {
		if(tmp.digit[i]+excess >= 10) {
			temp = tmp.digit[i]+excess;
			tmp.digit[i] = temp % 10;
			excess = temp / 10;
		} else {
			tmp.digit[i] = tmp.digit[i] + excess;
			excess = 0;
		}
	}
	
	for (i = MAXDIGIT-1 ; i >= 0 ; i--) {
		if (tmp.digit[i] != 0) {
			tmp.size = i+1;
			break;
		}
	}
	return tmp;
}

BigInteger& BigInteger::operator*=(int num)
{
	int excess = 0;
	BigInteger tmp(0);
	for (int i = 0 ; i <= MAXDIGIT-1 ; i++) {
		if ((this->digit[i] * num) % 10 + excess >= 10) {
			tmp.digit[i] = (((this->digit[i] * num) % 10) + excess - 10);
			excess = (this->digit[i] * num) / 10 + 1;
		} else {
			tmp.digit[i] = (this->digit[i] * num) % 10 + excess;
			excess = (this->digit[i] * num) / 10;
		}
	}
	for (int i = MAXDIGIT-1 ; i >= 0 ; i--) {
		if (tmp.digit[i] != 0) {
			tmp.size = i+1;
			break;
		}
	}
	*this = tmp;
	return *this;
}

BigInteger& BigInteger::operator/=(int num)
{
	int rest = 0;
	BigInteger tmp(0);
	for (int i = this->size-1 ; i >= 0 ; i--) {
		tmp.digit[i] = (this->digit[i] + rest * 10) / num;
		rest = (this->digit[i] + rest * 10) % num;
	}
	for (int i = MAXDIGIT-1 ; i >= 0 ; i--) {
		if (tmp.digit[i] != 0) {
			tmp.size = i+1;
			break;
		}
	}
	*this = tmp;
	return *this;
}

BigInteger& BigInteger::operator=(const BigInteger& input)//problems
{
	this->size = input.size;
	for (int i = 0 ; i < MAXDIGIT ; i++) {
		this->digit[i] = input.digit[i];
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& input)
{
	if (input.size == 0) {
		out << "0";
	} else {
		for (int i = input.size - 1 ; i >= 0 ; i--) 
			out << input.digit[i];
	}
	return out;
}

bool BigInteger::iseven()
{
	return (digit[0] % 2 == 0)? true : false;
}

bool BigInteger::iszero()
{
	return (size == 0)? true : false;
}