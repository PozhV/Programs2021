//============================================================================
// Name        : rw5_group_heavy_strings.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include<set>

using namespace std;
template <typename String>
using Group = vector<String>;
template <typename String>
using Char = typename String::value_type;
template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	vector<Group<String>> vectors;
	map<set<Char<String>>, size_t> set_chars;
	size_t count_groups = 0;
	for(auto it = strings.begin(); it != strings.end(); it++)
	{
		set<Char<String>> unique_char;
		for(auto item: *it)
			unique_char.insert(move(item));
		if(set_chars.count(unique_char) == 0)
		{
			set_chars[move(unique_char)] = count_groups;
			count_groups++;
			vectors.resize(count_groups);
			vectors[count_groups - 1].push_back(move(*it));

		}
		else{
			vectors[set_chars.at(unique_char)].push_back(move(*it));
		}
		//for(auto item: unique_char)
		//	cout<<item<<" ";
		//cout<<endl;
	}
	return vectors;

}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}
void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}
