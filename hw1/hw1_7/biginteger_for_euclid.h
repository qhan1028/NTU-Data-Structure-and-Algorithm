#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

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
  const BigInteger operator%(const BigInteger&) const;
  const BigInteger operator-(const BigInteger&) const;
  BigInteger& operator=(const BigInteger&);
  BigInteger& operator*=(int);
  BigInteger& operator/=(int);

  const bool iszero() const;

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

};


#endif