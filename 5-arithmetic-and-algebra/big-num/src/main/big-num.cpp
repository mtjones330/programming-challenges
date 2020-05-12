#include <iostream>
#include "big-num.h"

BigNum::BigNum()
  : digits(new char[MAXDIGITS]), nDigits(1), signBit(PLUS)
{
  initDigits();
}

BigNum::BigNum(std::string str)
  : digits(new char[MAXDIGITS])
{
  initDigits();

  if (str[0] == '+' || str[0] == '-') {
    signBit = str[0] == '+' ? PLUS : MINUS;
    str = str.substr(1);
  }
  else {
    signBit = PLUS;
  }

  nDigits = str.length();

  for (int i = 0; i < nDigits; i++) {
    digits[i] = str[nDigits - 1 - i];
  }
}

void BigNum::initDigits()
{
  for (int i = 0; i < MAXDIGITS; i++)
  {
    digits[i] = '0';
  }
}

BigNum::~BigNum()
{
  delete[] digits;
}

BigNum& BigNum::operator=(const BigNum &n)
{
  if (&n == this)
  {
    return *this;
  }

  for (int i = 0; i < MAXDIGITS; i++)
  {
    digits[i] = n.digits[i];
  }

  nDigits = n.nDigits;
  signBit = n.signBit;

  return *this;
}

BigNum::BigNum(BigNum &&n)
  : digits(n.digits), nDigits(n.nDigits), signBit(n.signBit)
{
  n.nDigits = 0;
  n.digits = nullptr;
}

BigNum& BigNum::operator=(BigNum &&n)
{
  if (&n == this)
  {
    return *this;
  }

  delete[] digits;

  digits = n.digits;
  nDigits = n.nDigits;
  signBit = n.signBit;

  n.nDigits = 0;
  n.digits = nullptr;

  return *this;
}

BigNum BigNum::operator+ (BigNum &n)
{
  BigNum c;
  addBigNum(this, &n, &c);
  return c;
}

BigNum BigNum::operator- (BigNum &n)
{
  BigNum c;
  subtractBigNum(this, &n, &c);
  return c;
}

BigNum BigNum::operator* (BigNum &n)
{
  BigNum c;
  multiplyBigNum(this, &n, &c);
  return c;
}

bool BigNum::operator< (BigNum &n)
{
  if (compareBigNum(this, &n) == LESSTHAN)
  {
    return true;
  }

  return false;
}

bool BigNum::operator== (BigNum &n)
{
  if(compareBigNum(this, &n) == EQUALTO)
  {
    return true;
  }

  return false;
}

bool BigNum::operator!= (BigNum &n)
{
  return !(*this == n);
}

bool BigNum::operator> (BigNum &n)
{
  if (compareBigNum(this, &n) == GREATERTHAN)
  {
    return true;
  }

  return false;
}

int BigNum::compareBigNum(BigNum *a, BigNum *b)
{
  if (a->signBit == MINUS && b->signBit == PLUS) return LESSTHAN;
  if (a->signBit == PLUS && b->signBit == MINUS) return GREATERTHAN;

  if (a->signBit == PLUS && b->signBit == PLUS)
  {
    if (a->nDigits < b->nDigits) return LESSTHAN;
    if (a->nDigits > b->nDigits) return GREATERTHAN;
  }

  if (a->signBit == MINUS && b->signBit == MINUS)
  {
    if (a->nDigits < b->nDigits) return GREATERTHAN;
    if (a->nDigits > b->nDigits) return LESSTHAN;
  }

  for (int i = a->nDigits - 1; i >= 0; i--)
  {
    if (a->digits[i] > b->digits[i]) return PLUS * a->signBit;
    if (a->digits[i] < b->digits[i]) return MINUS * a->signBit;
  }

  return EQUALTO;
}

void BigNum::adjustDigits()
{
  while (nDigits > 0 && toInt(digits[nDigits]) == 0)
  {
    nDigits--;
  }

  if (nDigits == 0 && toInt(digits[0]) == 0)
  {
    signBit = PLUS;
  }

  nDigits++;
}


void BigNum::subtractBigNum(BigNum *a, BigNum *b, BigNum *c)
{
  if (a->signBit == MINUS || b->signBit == MINUS)
  {
    b->signBit = -1 * b->signBit;
    addBigNum(a, b, c);
    b->signBit = -1 * b->signBit;
    return;
  }

  if (*a < *b)
  {
    subtractBigNum(b, a, c);
    c->signBit = MINUS;
    return;
  }

  c->nDigits = std::max(a->nDigits, b->nDigits);

  int borrow = 0;

  for (int i = 0; i <= c->nDigits; i++)
  {
    int v = toInt(a->digits[i]) - borrow - toInt(b->digits[i]);

    if (toInt(a->digits[i]) > 0)
    {
      borrow = 0;
    }

    if (v < 0)
    {
      v += 10;
      borrow = 1;
    }

    c->digits[i] = toChar(v % 10);
  }

  c->adjustDigits();
}

void BigNum::addBigNum(BigNum *a, BigNum *b, BigNum *c)
{
  if (a->signBit == b->signBit)
  {
    c->signBit = a->signBit;
  }

  else
  {
    if (a->signBit == MINUS)
    {
      a->signBit = PLUS;
      subtractBigNum(b, a, c);
      a->signBit = MINUS;
    }

    else
    {
      b->signBit  = PLUS;
      subtractBigNum(a, b, c);
      b->signBit = MINUS;
    }

    return;
  }

  c->nDigits = a->nDigits + b->nDigits;

  int carry = 0;

  for (int i = 0; i <= (c->nDigits); i++)
  {
    int addend = carry + toInt(a->digits[i]) + toInt(b->digits[i]);

    c->digits[i] = toChar(addend % 10);
    carry = addend / 10;
  }

  c->adjustDigits();
}

void BigNum::multiplyBigNum(BigNum *a, BigNum *b, BigNum *c)
{
  BigNum row;
  BigNum tmp;

  row = *a;

  for (int i = 0; i < b->nDigits; i++)
  {
    for (int j = 1; j <= toInt(b->digits[i]); j++)
    {
      addBigNum(c, &row, &tmp);
      *c = tmp;
    }

    digitShift(&row, 1);
  }

  c->signBit = a->signBit * b->signBit;

  c->adjustDigits();
}

void BigNum::digitShift(BigNum *n, int d)
{
  if (n->nDigits == 0 && toInt(n->digits[0]) == 0)
  {
    return;
  }

  for (int i = n->nDigits; i >= 0; i--)
  {
    n->digits[i + d] = n->digits[i];
  }

  for (int i = 0; i < d; i++)
  {
    n->digits[i] = toChar(0);
  }

  n->nDigits = n->nDigits + d;
}

int BigNum::toInt(char c)
{
  return c - '0';
}

char BigNum::toChar(int d)
{
  return d + '0';
}

std::string BigNum::toString()
{
  std::string result = "";

  if (signBit == MINUS && !(nDigits == 1 && digits[0] == '0'))
  {
    result += "-";
  }

  for (int i = 0; i < nDigits; i++)
  {
    result += digits[nDigits - 1 - i];
  }

  return result;
}

std::ostream & operator<< (std::ostream &out, BigNum &n)
{
  return out << n.toString();
}
