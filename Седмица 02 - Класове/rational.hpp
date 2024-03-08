#ifndef HPP_RATIONAL
#define HPP_RATIONAL

class Rational {
public:
  Rational(int, int);
  int getNumerator() const;
  int getDenominator() const;
  void setNumerator(int);
  void setDenominator(int);

private:
  int numerator;
  int denominator;

  void simplify();
  int find_gcd() const;
};

#endif