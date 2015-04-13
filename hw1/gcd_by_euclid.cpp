#include <iostream>

#include "biginteger_for_euclid.h"

using namespace std;

BigInteger gcd_by_euclid(const BigInteger& a, BigInteger& b){
  BigInteger n, m;

  if (a < b){
    n = a; m = b;
  }
  else{
    n = b; m = a;
  }

  while(!((m % n).iszero())){
    BigInteger tmp;
    tmp = n; 
    n = m % n; 
    m = tmp;
  }

  return n;
}

int main(){
  string sa, sb;
  cin >> sa >> sb;
  BigInteger a(sa), b(sb);

  cout << gcd_by_euclid(a, b) << endl;

  return 0;
}