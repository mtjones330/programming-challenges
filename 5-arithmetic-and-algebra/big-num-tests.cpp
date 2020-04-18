#include <iostream>
#include <vector>
#include "big-num.h"
using namespace std;

#define RED     "\033[31m"

void runTests();
void toStringTests();
void comparisonTests();
void additionTests();

struct ToStringTestCase {
  string input;
  string expected;

  ToStringTestCase (string _input, string _expected) {
    input = _input;
    expected = _expected;
  };
};

struct ComparisonTestCase {
  BigNum a;
  BigNum b;
  bool isLessThan;
  bool isEqual;
  bool isNotEqual;
  bool isGreaterThan;

  ComparisonTestCase(BigNum *_a, BigNum *_b, bool _isLessThan, bool _isEqual, bool _isNotEqual, bool _isGreaterThan) {
    a = *_a;
    b = *_b;
    isLessThan = _isLessThan;
    isEqual = _isEqual;
    isNotEqual = _isNotEqual;
    isGreaterThan = _isGreaterThan;
  }
};

int main() {
  runTests();
}

void runTests() {
  toStringTests();
  comparisonTests();
}

void toStringTests() {
  vector<ToStringTestCase> testCases = {
    ToStringTestCase("0", "0"),
    ToStringTestCase("+0", "0"),
    ToStringTestCase("-0", "0"),
    ToStringTestCase("1", "1"),
    ToStringTestCase("+1", "1"),
    ToStringTestCase("-1", "-1"),
    ToStringTestCase("10", "10"),
    ToStringTestCase("+10", "10"),
    ToStringTestCase("-10", "-10"),
    ToStringTestCase("10000000000000000000", "10000000000000000000"),
    ToStringTestCase("+10000000000000000000", "10000000000000000000"),
    ToStringTestCase("-10000000000000000000", "-10000000000000000000")
  };

  for (int i = 0; i < testCases.size(); i++) {
    ToStringTestCase tc = testCases.at(i);

    string actual = BigNum(tc.input).toString();

    if (actual != tc.expected) {
      cout << RED << tc.input << " => expected: " << tc.expected << ", actual: " << actual << endl;
    }
  }
}

void comparisonTests() {
  vector<ComparisonTestCase> testCases = {
    ComparisonTestCase(new BigNum("-1"), new BigNum("-1"), false, true, false, false),
    ComparisonTestCase(new BigNum("-1"), new BigNum("0"), true, false, true, false),
    ComparisonTestCase(new BigNum("-1"), new BigNum("1"), true, false, true, false),
    ComparisonTestCase(new BigNum("0"), new BigNum("-1"), false, false, true, true),
    ComparisonTestCase(new BigNum("0"), new BigNum("0"), false, true, false, false),
    ComparisonTestCase(new BigNum("0"), new BigNum("1"), true, false, true, false),
    ComparisonTestCase(new BigNum("1"), new BigNum("-1"), false, false, true, true),
    ComparisonTestCase(new BigNum("1"), new BigNum("0"), false, false, true, true),
    ComparisonTestCase(new BigNum("1"), new BigNum("1"), false, true, false, false),

    ComparisonTestCase(new BigNum("-12"), new BigNum("-12"), false, true, false, false),
    ComparisonTestCase(new BigNum("-12"), new BigNum("0"), true, false, true, false),
    ComparisonTestCase(new BigNum("-12"), new BigNum("12"), true, false, true, false),
    ComparisonTestCase(new BigNum("0"), new BigNum("-12"), false, false, true, true),
    ComparisonTestCase(new BigNum("0"), new BigNum("0"), false, true, false, false),
    ComparisonTestCase(new BigNum("0"), new BigNum("12"), true, false, true, false),
    ComparisonTestCase(new BigNum("12"), new BigNum("-12"), false, false, true, true),
    ComparisonTestCase(new BigNum("12"), new BigNum("0"), false, false, true, true),
    ComparisonTestCase(new BigNum("12"), new BigNum("12"), false, true, false, false),

    ComparisonTestCase(new BigNum("-1"), new BigNum("-12"), false, false, true, true),
    ComparisonTestCase(new BigNum("-12"), new BigNum("0"), true, false, true, false),
    ComparisonTestCase(new BigNum("-1"), new BigNum("12"), true, false, true, false),
    ComparisonTestCase(new BigNum("0"), new BigNum("-12"), false, false, true, true),
    ComparisonTestCase(new BigNum("0"), new BigNum("12"), true, false, true, false),
    ComparisonTestCase(new BigNum("1"), new BigNum("-12"), false, false, true, true),
    ComparisonTestCase(new BigNum("12"), new BigNum("0"), false, false, true, true),
    ComparisonTestCase(new BigNum("1"), new BigNum("12"), true, false, true, false),
  };

  for (int i = 0; i < testCases.size(); i++) {
    ComparisonTestCase tc = testCases.at(i);

    bool isLessThan = tc.a < tc.b;
    bool isEqual = tc.a == tc.b;
    bool isNotEqual = tc.a != tc.b;
    bool isGreaterThan = tc.a > tc.b;


    if (isLessThan != tc.isLessThan) {
      cout << tc.a << " < " << tc.b << " => expected: " << tc.isLessThan << ", actual: " << isLessThan << endl;
    }

    if (isEqual != tc.isEqual) {
      cout << tc.a << " == " << tc.b << " => expected: " << tc.isEqual << ", actual: " << isEqual << endl;
    }

    if (isNotEqual != tc.isNotEqual) {
      cout << tc.a << " != " << tc.b << " => expected: " << tc.isNotEqual << ", actual: " << isNotEqual << endl;
    }

    if (isGreaterThan != tc.isGreaterThan) {
      cout << tc.a << " > " << tc.b << " => expected: " << tc.isGreaterThan << ", actual: " << isGreaterThan << endl;
    }
  }
}


void additionTests() {
  char strA[MAXDIGITS];
  char strB[MAXDIGITS];
  char strExpected[MAXDIGITS];
  char equal;
  char opp;

  while(scanf("%s %c %s %c %s", strA, &opp, strB, &equal, strExpected) != EOF) {
    BigNum a = BigNum(strA);
    BigNum b = BigNum(strB);
    BigNum expected = BigNum(strExpected);
    BigNum actual = a + b;

    if (expected != actual) {
      cout << RED << a << " " << opp << " " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}