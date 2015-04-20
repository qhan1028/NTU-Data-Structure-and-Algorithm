#include <cstdio>
#include <iostream>
using namespace std;

int min(int a, int b)
{
	return (a > b)? b : a;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

void swap(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void GCD_Reverse_Search(int a, int b)
{
	cout << "Case (" << a << ", " << b << "): ";
	int count = 0;
	for (int i = min(a, b) ; i >= 1 ; i--) {
		count++;
		if (a % i == 0 && b % i == 0) {
			cout << "GCD-By-Reverse-Search = " << i << ", ";
			cout << "taking " << count << " iterations\n";
			return;
		}
	}
}

int GCD_Filter(int a, int b)
{
	for (int i = 2 ; i <= min(a, b) ; i++) {
		if (a % i == 0 && b % i == 0) {
			return i * GCD_Filter(a/i, b/i);
		}
	}
	return 1;
}

int GCD_Filter_count(int a, int b)
{
	int count = 0;
	for (int i = 2 ; i <= min(a, b) ; i++) {
		count++;
		if (a % i == 0 && b % i == 0) {
			return count + GCD_Filter_count(a/i, b/i);
		}
	}
	return count;
}

int GCD_Filter_Faster(int a, int b, int s)
{
	for (int i = s ; i <= min(a, b) ; i++) {
		if (a % i == 0 && b % i == 0) {
			return i * GCD_Filter_Faster(a/i, b/i, i);
		}
	}
	return 1;
}

int GCD_Filter_Faster_count(int a, int b, int s)
{
	int count = 0;
	for (int i = s ; i <= min(a, b) ; i++) {
		count++;
		if (a % i == 0 && b % i == 0) {
			return count + GCD_Filter_Faster_count(a/i, b/i, i);
		}
	}
	return count;
}

void GCD_Binary(int a, int b)
{
	int n = min(a, b), m = max(a, b);
	int ans = 1, count = 0;
	while(n*m != 0) {
		count++;
		if (n%2 == 0 && m%2 == 0) {
			ans *= 2;
			n /= 2;
			m /= 2;
		}
		else if (n%2 == 0 && m%2 != 0) n /= 2;
		else if (n%2 != 0 && m%2 == 0) m /= 2;
		if (n > m) swap(n, m);
		m -= n;
	}
	cout << "Case (" << a << ", " << b << "): ";
	printf("GCD-By-Binary = %d, taking %d iterations\n", ans*n, count);
}

void GCD_Euclid(int a, int b)
{
	int n = min(a, b), m = max(a, b);
	int tmp, count = 0;
	while (m % n != 0) {
		count++;
		tmp = n;
		n = m % n;
		m = tmp;
	}
	cout << "Case (" << a << ", " << b << "): ";
	printf("GCD-By-Euclid = %d, taking %d iterations\n", n, count);
}

int main()
{
	int num1, num2, tmp1, tmp2;

	cin >> num1 >> num2;

	while (num1 != 0) {
		GCD_Reverse_Search(num1, num2);

		tmp1 = GCD_Filter(num1, num2);
		tmp2 = GCD_Filter_count(num1, num2);
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Filter = %d, taking %d iterations\n", tmp1, tmp2);
		
		tmp1 = GCD_Filter_Faster(num1, num2, 2);
		tmp2 = GCD_Filter_Faster_count(num1, num2, 2);
		printf("Case (%d, %d): ", num1, num2);
		printf("GCD-By-Filter-Faster = %d, taking %d iterations\n", tmp1, tmp2);

		GCD_Binary(num1, num2);

		GCD_Euclid(num1, num2);
		
		cin >> num1 >> num2;
	}
	return 0;
}