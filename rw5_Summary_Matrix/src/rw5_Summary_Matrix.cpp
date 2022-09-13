//============================================================================
// Name        : rw5_Summary_Matrix.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"
#include <vector>
#include<algorithm>
#include<future>
#include <numeric>
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  size_t k = min(size_t(4), matrix.size());
  size_t d = matrix.size()/k;
  if(matrix.size() % k != 0) d++;
  int64_t sum = 0;
  vector<future<int64_t>> f;
  for(size_t i = 0; i < k; i++)
  {
	  f.push_back(async([&matrix, i, d]{int64_t sum = 0;
	  for(auto it = matrix.begin() + i*d; (it < matrix.end() && it < matrix.begin() + (i+1)*d); it++)
	  	  sum += accumulate(it->begin(), it->end(), 0);
	  return sum;}));
  }
  for(auto& i: f)
  {
	  sum += i.get();
  }
  return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
    {1, 1, 1, 1},
    {2, 2, 2, 2},
	{3, 3, 3, 3}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 160);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
