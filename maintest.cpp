#include <iostream>
#include "test.h"

using namespace std;

// initailization test... pass
// cout test... pass
// operator test... < *= = - /= 
// is zero iseven test... pass

int main()
{
	BigInteger n(1100);
	BigInteger m(11);
	n /= 100;
	cout << n;

	return 0;
}