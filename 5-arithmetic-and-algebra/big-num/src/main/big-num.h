#ifndef BIG_NUM
#define BIG_NUM

#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1
#define LESSTHAN -1
#define EQUALTO 0
#define GREATERTHAN 1

class BigNum {
  private:
    char* digits;
    int nDigits;
    int signBit;

    void initDigits();
    void digitShift(BigNum *n, int d);
    void addBigNum(BigNum *a, BigNum *b, BigNum *c);
    void subtractBigNum(BigNum *a, BigNum *b, BigNum *c);
    void multiplyBigNum(BigNum *a, BigNum *b, BigNum *c);
    void adjustDigits();
    int compareBigNum(BigNum *a, BigNum*b);
    int toInt(char c);
    char toChar(int d);

  public:
    BigNum();
    BigNum(std::string str);
    ~BigNum();
    BigNum(BigNum &&n);
    BigNum& operator=(const BigNum &n);
    BigNum& operator=(BigNum &&n);


    BigNum operator+ (BigNum &n);
    BigNum operator- (BigNum &n);
    BigNum operator* (BigNum &n);

    bool operator< (BigNum &n);
    bool operator== (BigNum &n);
    bool operator!= (BigNum &n);
    bool operator> (BigNum &n);

    std::string toString();
};

std::ostream & operator<<(std::ostream &out, BigNum &n);

#endif
