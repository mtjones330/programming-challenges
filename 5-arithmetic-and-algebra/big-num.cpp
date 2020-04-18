#include <iostream>
#include "big-num.h"


BigNum::BigNum() {
  init();
}

BigNum::BigNum(std::string str) {
  init();

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


void BigNum::init() {
  signBit = PLUS;
  nDigits = 1;

  for (int i = 0; i < MAXDIGITS; i++) {
    digits[i] = '0';
  }
}

BigNum BigNum::operator+ (BigNum &n) {
  BigNum c;

  addBigNum(this, &n, &c);

  return c;
}

bool BigNum::operator< (BigNum &n) {
  if (compareBigNum(this, &n) == -1) {
    return true;
  }

  return false;
}

bool BigNum::operator== (BigNum &n) {
  if(compareBigNum(this, &n) == 0) {
    return true;
  }

  return false;
}

bool BigNum::operator!= (BigNum &n) {
  return !(*this == n);
}

bool BigNum::operator> (BigNum &n) {
  if (compareBigNum(this, &n) == 1) {
    return true;
  }

  return false;
}

int BigNum::compareBigNum(BigNum *a, BigNum * b) {
  if (a->signBit == MINUS && b->signBit == PLUS) return PLUS;
  if (a->signBit == PLUS && b->signBit == MINUS) return MINUS;

  if (a->nDigits < b->nDigits) return PLUS;
  if (a->nDigits > b->nDigits) return MINUS;

  for (int i = a->nDigits; i >= 0; i--) {
    if (a->digits[i] < b->digits[i]) return a->signBit;
    if (a->digits[i] > b->digits[i]) return MINUS * a->signBit;
  }

  return 0;
}

void BigNum::zeroJustify(BigNum *n) {
  while (n->nDigits > 0 && toInt(n->digits[n->nDigits]) == 0) {
    n->nDigits--;
  }

  if (n->nDigits == 0 && toInt(n->digits[0]) == 0) {
    n->signBit = PLUS;
  }
}


void BigNum::subtractBigNum(BigNum *a, BigNum* b, BigNum* c) {
  if (a->signBit == MINUS || b->signBit == MINUS) {
    b->signBit = -1 * b->signBit;
    addBigNum(a, b, c);
    b->signBit = -1 * b->signBit;
    return;
  }

  if (compareBigNum(a, b) == PLUS) {
    subtractBigNum(b, a, c);
    c->signBit = MINUS;
    return;
  }

  c->nDigits = std::max(a->nDigits, b->nDigits);

  int borrow = 0;

  for (int i = 0; i <= c->nDigits; i++) {
    int v = toInt(a->digits[i]) - borrow - toInt(b->digits[i]);

    if (toInt(a->digits[i]) > 0) {
      borrow = 0;
    }

    if (v < 0) {
      v += 10;
      borrow = 1;
    }

    c->digits[i] = toChar(v % 10);
  }

  zeroJustify(c);
}

void BigNum::addBigNum(BigNum *a, BigNum *b, BigNum *c) {
  if (a->signBit == b->signBit) {
    c->signBit = a->signBit;
  }

  else {
    if (a->signBit == MINUS) {
      a->signBit = PLUS;
      subtractBigNum(b, a, c);
      a->signBit = MINUS;
    }

    else {
      b->signBit  = PLUS;
      subtractBigNum(a, b, c);
      b->signBit = MINUS;
    }

    return;
  }

  c->nDigits = a->nDigits + b->nDigits;

  int carry = 0;

  for (int i = 0; i <= (c->nDigits); i++) {
    int addend = carry + toInt(a->digits[i]) + toInt(b->digits[i]);

    c->digits[i] = toChar(addend % 10);
    carry = addend / 10;
  }

  zeroJustify(c);
}

void BigNum::digitShift(BigNum *n, int d) {
  if (n->nDigits == 0 && toInt(n->digits[0]) == 0) {
    return;
  }

  for (int i = n->nDigits; i >= 0; i--) {
    n->digits[i + d] = n->digits[i];
  }

  for (int i = 0; i < d; i++) {
    n->digits[i] = toChar(0);
  }

  n->nDigits = n->nDigits + d;
}

void BigNum::multiplyBigNum(BigNum *a, BigNum *b, BigNum *c) {
  BigNum row;
  BigNum tmp;

  row = *a;

  for (int i = 0; i <= b->nDigits; i++) {
    for (int j = 1; j <= toInt(b->digits[i]); j++) {
      addBigNum(c, &row, &tmp);
      *c = tmp;
    }

    digitShift(&row, 1);
  }

  c->signBit = a->signBit * b->signBit;

  zeroJustify(c);
}

int BigNum::toInt(char c) {
  return c - '0';
}

char BigNum::toChar(int d) {
  return d + '0';
}

BigNum BigNum::toBigNum(char str[]) {
  BigNum n;
  int nDigits = 1;

  while(toInt(str[nDigits] != 0)) {
    nDigits++;
  }

  n.nDigits = nDigits;

  int shift = 0;

  if (str[0] == '+') {
    n.signBit = PLUS;
    shift = 1;
  }
  else if (str[0] == '-') {
    n.signBit = MINUS;
    shift = 1;
  }

  for (int i = 0; i < nDigits; i++) {
    char tmp = str[i + shift];
    n.digits[i] = str[nDigits - 1 - i];
    str[nDigits - 1 - i] = tmp;
  }
}

std::string BigNum::toString() {
  std::string result = "";

  if (signBit == MINUS && !(nDigits == 1 && digits[0] == '0')) {
    result += "-";
  }

  for (int i = 0; i < nDigits; i++) {
    result += digits[nDigits - 1 - i];
  }

  return result;
}

std::ostream & operator<< (std::ostream &out, BigNum &n) {
  return out << n.toString();
}
