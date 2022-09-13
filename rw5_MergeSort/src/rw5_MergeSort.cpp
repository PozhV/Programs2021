//============================================================================
// Name        : rw5_MergeSort.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;
template <typename RandomIt>
using Type = typename RandomIt::value_type;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int dist = (range_end - range_begin)/3;
	if(range_end - range_begin < 2) return;
	vector<Type<RandomIt>> vec, vec_;
	move(range_begin, range_end, back_inserter(vec));
	for(auto it = vec.begin(); it != vec.end(); it += dist)
		MergeSort(it, it + dist);
	merge(make_move_iterator(vec.begin()), make_move_iterator(vec.begin()) + dist, make_move_iterator(vec.begin()) + dist, make_move_iterator(vec.begin()) + 2 * dist, back_inserter(vec_));
	merge(make_move_iterator(vec_.begin()), make_move_iterator(vec_.begin() + 2 * dist), make_move_iterator(vec.begin() + 2 * dist), make_move_iterator(vec.begin() + 3 * dist), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
