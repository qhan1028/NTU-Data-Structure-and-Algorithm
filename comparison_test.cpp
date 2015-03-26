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

int GCD_Reverse_Search(int a, int b)
{
	int count = 0;
	for (int i = min(a, b) ; i >= 1 ; i--) {
		count++;
		if (a % i == 0 && b % i == 0) {
			return count;
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

int GCD_Binary(int a, int b)
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
	return count;
}

int GCD_Euclid(int a, int b)
{
	int n = min(a, b), m = max(a, b);
	int tmp, count = 0;
	while (m % n != 0) {
		count++;
		tmp = n;
		n = m % n;
		m = tmp;
	}
	return count;
}


int main()
{
	 sumRS = 0, sumF = 0, sumFF = 0, sumB = 0, sumE = 0;

	for (int i = 0 ; i <= 2260 ; i++) {
		sumRS += GCD_Reverse_Search(11260, 52000+i);
		sumF += GCD_Filter_count(11260, 52000+i);
		sumFF += GCD_Filter_Faster_count(11260, 52000+i, 2);
		sumB += GCD_Binary(11260, 52000+i);
		sumE += GCD_Euclid(11260, 52000+i);
	}
	printf("Reverse_Search %d\nFilter %d\nFilter_Faster %d\nBinary %d\nEuclid %d\n", sumRS/2261, sumF/2261, sumFF/2261, sumB/2261, sumE/2261);
	return 0;
}