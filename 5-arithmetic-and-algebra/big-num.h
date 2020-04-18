#ifndef BIG_NUM
#define BIG_NUM

#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1

class BigNum {
  private:
    char digits[MAXDIGITS];
    int nDigits;
    int signBit;
    void init();
    void digitShift(BigNum *n, int d);
    void addBigNum(BigNum *a, BigNum *b, BigNum *c);
    void subtractBigNum(BigNum *a, BigNum *b, BigNum *c);
    void multiplyBigNum(BigNum *a, BigNum *b, BigNum *c);
    void zeroJustify(BigNum *n);
    int compareBigNum(BigNum *a, BigNum*b);
    int toInt(char c);
    char toChar(int d);
    BigNum toBigNum(char str[]);

  public:
    BigNum();
    BigNum(std::string str);
    BigNum operator+ (BigNum &n);
    bool operator< (BigNum &n);
    bool operator== (BigNum &n);
    bool operator!= (BigNum &n);
    bool operator> (BigNum &n);
    std::string toString();
};

std::ostream & operator<<(std::ostream &out, BigNum &n);

#endif