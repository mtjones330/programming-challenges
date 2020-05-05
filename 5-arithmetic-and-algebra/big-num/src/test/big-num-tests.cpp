#include <iostream>
#include <vector>
#include "../main/big-num.h"
using namespace std;

void toStringTests();
void comparisonTests();
void additionTests();
void subtractionTests();

struct ToStringTestCase {
  string input;
  string expected;

  ToStringTestCase (string _input, string _expected) {
    input = _input;
    expected = _expected;
  };
};

struct ComparisonTestCase {
  string a;
  string b;
  bool isLessThan;
  bool isEqual;
  bool isNotEqual;
  bool isGreaterThan;

  ComparisonTestCase(string _a, string _b, bool _isLessThan, bool _isEqual, bool _isNotEqual, bool _isGreaterThan) {
    a = _a;
    b = _b;
    isLessThan = _isLessThan;
    isEqual = _isEqual;
    isNotEqual = _isNotEqual;
    isGreaterThan = _isGreaterThan;
  }
};

struct MathTestCase {
  string a;
  string b;
  string expected;

  MathTestCase(string _a, string _b, string _expected) {
    a = _a;
    b = _b;
    expected = _expected;
  }
};

int main() {
  toStringTests();
  comparisonTests();
  additionTests();
  subtractionTests();
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

  for (uint i = 0; i < testCases.size(); i++) {
    ToStringTestCase tc = testCases.at(i);

    string actual = BigNum(tc.input).toString();

    if (actual != tc.expected) {
      cout << tc.input << " == expected: " << tc.expected << ", actual: " << actual << endl;
    }
  }
}

void comparisonTests() {
  vector<ComparisonTestCase> testCases = {
    ComparisonTestCase("-1", "-1", false, true, false, false),
    ComparisonTestCase("-1", "0", true, false, true, false),
    ComparisonTestCase("-1", "1", true, false, true, false),
    ComparisonTestCase("0", "-1", false, false, true, true),
    ComparisonTestCase("0", "0", false, true, false, false),
    ComparisonTestCase("0", "1", true, false, true, false),
    ComparisonTestCase("1", "-1", false, false, true, true),
    ComparisonTestCase("1", "0", false, false, true, true),
    ComparisonTestCase("1", "1", false, true, false, false),

    ComparisonTestCase("-12", "-12", false, true, false, false),
    ComparisonTestCase("-12", "0", true, false, true, false),
    ComparisonTestCase("-12", "12", true, false, true, false),
    ComparisonTestCase("0", "-12", false, false, true, true),
    ComparisonTestCase("0", "0", false, true, false, false),
    ComparisonTestCase("0", "12", true, false, true, false),
    ComparisonTestCase("12", "-12", false, false, true, true),
    ComparisonTestCase("12", "0", false, false, true, true),
    ComparisonTestCase("12", "12", false, true, false, false),

    ComparisonTestCase("-1", "-12", false, false, true, true),
    ComparisonTestCase("-12", "0", true, false, true, false),
    ComparisonTestCase("-1", "12", true, false, true, false),
    ComparisonTestCase("0", "-12", false, false, true, true),
    ComparisonTestCase("0", "12", true, false, true, false),
    ComparisonTestCase("1", "-12", false, false, true, true),
    ComparisonTestCase("12", "0", false, false, true, true),
    ComparisonTestCase("1", "12", true, false, true, false),
  };

  for (uint i = 0; i < testCases.size(); i++) {
    ComparisonTestCase tc = testCases.at(i);

    BigNum a = BigNum(tc.a);
    BigNum b = BigNum(tc.b);

    bool isLessThan = a < b;
    bool isEqual = a == b;
    bool isNotEqual = a != b;
    bool isGreaterThan = a > b;

    if (isLessThan != tc.isLessThan) {
      cout << a << " < " << b << " == expected: " << tc.isLessThan << ", actual: " << isLessThan << endl;
    }

    if (isEqual != tc.isEqual) {
      cout << a << " == " << b << " == expected: " << tc.isEqual << ", actual: " << isEqual << endl;
    }

    if (isNotEqual != tc.isNotEqual) {
      cout << a << " != " << b << " == expected: " << tc.isNotEqual << ", actual: " << isNotEqual << endl;
    }

    if (isGreaterThan != tc.isGreaterThan) {
      cout << a << " > " << b << " == expected: " << tc.isGreaterThan << ", actual: " << isGreaterThan << endl;
    }
  }
}

void additionTests() {
  vector<MathTestCase> testCases = {
    MathTestCase("-1", "-1", "-2"),
    MathTestCase("-1", "0", "-1"),
    MathTestCase("-1", "1", "0"),
    MathTestCase("0", "-1", "-1"),
    MathTestCase("0", "0", "0"),
    MathTestCase("0", "1", "1"),
    MathTestCase("1", "-1", "0"),
    MathTestCase("1", "0", "1"),
    MathTestCase("1", "1", "2"),

    MathTestCase("-12", "-12", "-24"),
    MathTestCase("-12", "0", "-12"),
    MathTestCase("-12", "12", "0"),
    MathTestCase("0", "-12", "-12"),
    MathTestCase("0", "0", "0"),
    MathTestCase("0", "12", "12"),
    MathTestCase("12", "-12", "0"),
    MathTestCase("12", "0", "12"),
    MathTestCase("12", "12", "24"),

    MathTestCase("-1", "-12", "-13"),
    MathTestCase("-12", "0", "-12"),
    MathTestCase("-1", "12", "11"),
    MathTestCase("0", "-12", "-12"),
    MathTestCase("0", "12", "12"),
    MathTestCase("1", "-12", "-11"),
    MathTestCase("12", "0", "12"),
    MathTestCase("1", "12", "13"),
  };

  for (uint i = 0; i < testCases.size(); i++) {
    MathTestCase tc = testCases.at(i);

    BigNum a = BigNum(tc.a);
    BigNum b = BigNum(tc.b);
    BigNum expected = BigNum(tc.expected);
    BigNum actual = a + b;

    if (expected != actual) {
      cout << a << " + " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}

void subtractionTests() {
  vector<MathTestCase> testCases = {
    MathTestCase("-1", "-1", "0"),
    MathTestCase("-1", "0", "-1"),
    MathTestCase("-1", "1", "-2"),
    MathTestCase("0", "-1", "1"),
    MathTestCase("0", "0", "0"),
    MathTestCase("0", "1", "-1"),
    MathTestCase("1", "-1", "2"),
    MathTestCase("1", "0", "1"),
    MathTestCase("1", "1", "0"),

    MathTestCase("-12", "-12", "0"),
    MathTestCase("-12", "0", "-12"),
    MathTestCase("-12", "12", "-24"),
    MathTestCase("0", "-12", "12"),
    MathTestCase("0", "0", "0"),
    MathTestCase("0", "12", "-12"),
    MathTestCase("12", "-12", "24"),
    MathTestCase("12", "0", "12"),
    MathTestCase("12", "12", "0"),

    MathTestCase("-1", "-12", "11"),
    MathTestCase("-12", "0", "-12"),
    MathTestCase("-1", "12", "-13"),
    MathTestCase("0", "-12", "12"),
    MathTestCase("0", "12", "-12"),
    MathTestCase("1", "-12", "13"),
    MathTestCase("12", "0", "12"),
    MathTestCase("1", "12", "-11"),
  };

  for (uint i = 0; i < testCases.size(); i++) {
    MathTestCase tc = testCases.at(i);

    BigNum a = BigNum(tc.a);
    BigNum b = BigNum(tc.b);
    BigNum expected = BigNum(tc.expected);
    BigNum actual = a - b;

    if (expected != actual) {
      cout << a << " - " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}
