#ifndef BIGINTEGER_FOR_BINARY

#define BIGINTEGER_FOR_BINARY

class BigInteger{
public:
	int *digit;
	int size;

  BigInteger();
  BigInteger(const int&);
  BigInteger(const std::string&);
  BigInteger(const BigInteger&);
  ~BigInteger();

  bool operator<(const BigInteger&) const;
  const BigInteger operator-(const BigInteger&) const;
  const BigInteger operator*(const BigInteger&) const;
  BigInteger& operator*=(int);
  BigInteger& operator/=(int);
  BigInteger& operator=(const BigInteger&);
  bool iseven();
  bool iszero();

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	
};


#endif