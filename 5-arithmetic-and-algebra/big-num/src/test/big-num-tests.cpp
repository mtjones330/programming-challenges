#include <iostream>
#include <vector>
#include "../main/big-num.h"
using namespace std;

struct ToStringTestCase
{
  string input;
  string expected;

  ToStringTestCase (string _input, string _expected)
  {
    input = _input;
    expected = _expected;
  };
};

struct ComparisonTestCase
{
  string a;
  string b;
  bool isLessThan;
  bool isEqual;
  bool isNotEqual;
  bool isGreaterThan;

  ComparisonTestCase(string _a, string _b, bool _isLessThan, bool _isEqual, bool _isNotEqual, bool _isGreaterThan)
  {
    a = _a;
    b = _b;
    isLessThan = _isLessThan;
    isEqual = _isEqual;
    isNotEqual = _isNotEqual;
    isGreaterThan = _isGreaterThan;
  }
};

struct MathTestCase
{
  string a;
  string b;
  string expected;
  string sum;
  string difference;
  string product;

  MathTestCase(string _a, string _b, string _sum, string _difference, string _product)
  {
    a = _a;
    b = _b;
    sum = _sum;
    difference = _difference;
    product = _product;
  }
};

void toStringTests();
void comparisonTests();
void mathTests();
void additionTests(vector<MathTestCase> testCases);
void subtractionTests(vector<MathTestCase> testCases);
void multiplicationTests(vector<MathTestCase> testCases);
void divisionTests();

int main()
{
  toStringTests();
  comparisonTests();
  mathTests();
}

void mathTests() {
  vector<MathTestCase> testCases = {
    MathTestCase("-1", "-1", "-2", "0", "1"),
    MathTestCase("-1", "0", "-1", "-1", "0"),
    MathTestCase("-1", "1", "0", "-2", "-1"),
    MathTestCase("0", "-1", "-1", "1", "0"),
    MathTestCase("0", "0", "0", "0", "0"),
    MathTestCase("0", "1", "1", "-1", "0"),
    MathTestCase("1", "-1", "0", "2", "-1"),
    MathTestCase("1", "0", "1", "1", "0"),
    MathTestCase("1", "1", "2", "0", "1"),

    MathTestCase("-12", "-12", "-24", "0", "144"),
    MathTestCase("-12", "0", "-12", "-12", "0"),
    MathTestCase("-12", "12", "0", "-24", "-144"),
    MathTestCase("0", "-12", "-12", "12", "0"),
    MathTestCase("0", "0", "0", "0", "0"),
    MathTestCase("0", "12", "12", "-12", "0"),
    MathTestCase("12", "-12", "0", "24", "-144"),
    MathTestCase("12", "0", "12", "12", "0"),
    MathTestCase("12", "12", "24", "0", "144"),

    MathTestCase("-1", "-12", "-13", "11", "12"),
    MathTestCase("-12", "0", "-12", "-12", "0"),
    MathTestCase("-1", "12", "11", "-13", "-12"),
    MathTestCase("0", "-12", "-12", "12", "0"),
    MathTestCase("0", "12", "12", "-12", "0"),
    MathTestCase("1", "-12", "-11", "13", "-12"),
    MathTestCase("12", "0", "12", "12", "0"),
    MathTestCase("1", "12", "13", "-11", "12"),

    MathTestCase(UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED),
    MathTestCase(UNDEFINED, "12", UNDEFINED, UNDEFINED, UNDEFINED),
    MathTestCase("12", UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED)

  };

  additionTests(testCases);
  subtractionTests(testCases);
  multiplicationTests(testCases);
  divisionTests();
}

void toStringTests()
{
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

  for (uint i = 0; i < testCases.size(); i++)
  {
    auto tc = testCases.at(i);

    auto actual = BigNum(tc.input).toString();

    if (actual != tc.expected)
    {
      cout << tc.input << " == expected: " << tc.expected << ", actual: " << actual << endl;
    }
  }
}

void comparisonTests()
{
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
    ComparisonTestCase("undefined", "undefined", false, true, false, false),
    ComparisonTestCase("undefined", "12", false, false, true, false)
  };

  for (uint i = 0; i < testCases.size(); i++)
  {
    auto tc = testCases.at(i);

    auto a = BigNum(tc.a);
    auto b = BigNum(tc.b);

    auto isLessThan = a < b;
    auto isEqual = a == b;
    auto isNotEqual = a != b;
    auto isGreaterThan = a > b;

    if (isLessThan != tc.isLessThan)
    {
      cout << a << " < " << b << " == expected: " << tc.isLessThan << ", actual: " << isLessThan << endl;
    }

    if (isEqual != tc.isEqual)
    {
      cout << a << " == " << b << " == expected: " << tc.isEqual << ", actual: " << isEqual << endl;
    }

    if (isNotEqual != tc.isNotEqual)
    {
      cout << a << " != " << b << " == expected: " << tc.isNotEqual << ", actual: " << isNotEqual << endl;
    }

    if (isGreaterThan != tc.isGreaterThan)
    {
      cout << a << " > " << b << " == expected: " << tc.isGreaterThan << ", actual: " << isGreaterThan << endl;
    }
  }
}

void additionTests(vector<MathTestCase> testCases)
{
  for (uint i = 0; i < testCases.size(); i++)
  {
    auto tc = testCases.at(i);
    auto a = BigNum(tc.a);
    auto b = BigNum(tc.b);

    auto actual = a + b;

    auto expected = BigNum(tc.sum);

    if (expected != actual)
    {
      cout << a << " + " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}
void subtractionTests(vector<MathTestCase> testCases)
{
  for (uint i = 0; i < testCases.size(); i++)
  {
    auto tc = testCases.at(i);
    auto a = BigNum(tc.a);
    auto b = BigNum(tc.b);

    auto actual = a - b;

    auto expected = BigNum(tc.difference);

    if (expected != actual)
    {
      cout << a << " - " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}

void multiplicationTests(vector<MathTestCase> testCases)
{
  for (uint i = 0; i < testCases.size(); i++)
  {
    auto tc = testCases.at(i);
    auto a = BigNum(tc.a);
    auto b = BigNum(tc.b);

    auto actual = a * b;

    auto expected = BigNum(tc.product);

    if (expected != actual)
    {
      cout << a << " * " << b << " = expected: " << expected << ", actual: " << actual << endl;
    }
  }
}

void divisionTests()
{
  auto a = BigNum("0");
  auto b = BigNum("2");
  auto c = a / b;

  cout << c << endl;
}