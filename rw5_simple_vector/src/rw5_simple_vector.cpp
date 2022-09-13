//============================================================================
// Name        : rw5_simple_vector.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

void TestCopyAssignment() {
  SimpleVector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest;
  ASSERT_EQUAL(dest.Size(), 0u);

  dest = numbers;
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
  SimpleVector<int> des(numbers);
  ASSERT_EQUAL(des.Size(), numbers.Size());
  ASSERT(des.Capacity() >= des.Size());
  ASSERT(equal(des.begin(), des.end(), numbers.begin()));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCopyAssignment);
}
