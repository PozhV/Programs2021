//============================================================================
// Name        : rw5_PriorityCollection.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include<list>
#include <utility>
#include <vector>
using namespace std;

template<typename T>
class PriorityCollection {
public:

	struct Object {
	    T value;
	    int priority;
	};
	using Id = typename vector<Object>::iterator;
	friend const bool operator<(const typename vector<Object>::iterator& lhs, const typename vector<Object>::iterator& rhs)
	{
		bool b = false;
		if(lhs->priority < rhs->priority)
		{
			b = true;
		}
		else if(lhs->priority == rhs->priority)
		{
			if(lhs - rhs < 0)
				b = true;
		}
		return b;
	}
	PriorityCollection(){objects.reserve(1000000);}
    void Print()
    {
    	for(auto& x: ids)
    	{
    		cout<<x->value<<";"<<x->priority<<" ";
    	}
    	cout<<endl;
    }
    Id Add(T object) {
        objects.push_back({move(object), 0});
    	Id id = prev(objects.end());
        ids.insert(id);
        return id;
    }

    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt idsbegin) {
        for (; range_begin != range_end; range_begin = next(range_begin)) {
        	objects.push_back({ move(*range_begin), 0 });
        	Id id = prev(objects.end());
            ids.insert(id);
            *idsbegin = id;
            idsbegin++;
        }
    }
    bool IsValid(Id id) const {
        return ids.find(id) != ids.end();
    }
    const T& Get(Id id) const {
        return id->value;
    }
    void Promote(Id id) {
        ids.erase(id);
        id->priority++;
        ids.insert(id);
    }
    pair<const T &, int> GetMax() const {
        Id id = *prev(ids.end());
    	return {id->value, id->priority};
    }
    pair<T, int> PopMax() {
    	Id id = *prev(ids.end());
		auto p = make_pair(move(id->value), id->priority);
    	ids.erase(id);
    	return p;
    }


private:
    set<Id> ids;
    vector<Object> objects;
};
class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};
/*/bool operator<(const vector<vector<PriorityCollection<StringNonCopyable>::Object>::iterator>& lhs, const vector<vector<PriorityCollection<StringNonCopyable>::Object>::iterator>& rhs)
/*/

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  vector<vector<PriorityCollection<StringNonCopyable>::Object>::iterator> vec;
  vec.resize(5);
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  //for (int i = 0; i < 4; ++i) {
   // strings.Promote(white_id);
  //}
  strings.Promote(yellow_id);
  ASSERT_EQUAL(strings.GetMax().first, "red");
  StringNonCopyable str("ab");
  StringNonCopyable str1("abc");
  vector<StringNonCopyable> strs;// = {move("ab"), move("ba"), move("cb"), move("ca")};
  strs.push_back(move(str));
  strs.push_back(move(str1));
  strings.Add(strs.begin(), strs.end(), vec.begin());
  for (int i = 0; i < 4; ++i) {
    strings.Promote(vec[0]);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "ab");
    ASSERT_EQUAL(item.second, 4);
    ASSERT_EQUAL(strings.GetMax().second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
    ASSERT_EQUAL(strings.GetMax().second, 2);
  }
  ASSERT_EQUAL(strings.Get(vec[1]), "abc");
  for (int i = 0; i < 4; ++i) {
    strings.Promote(vec[1]);
  }
  ASSERT_EQUAL(strings.GetMax().second, 4);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "abc");
    ASSERT_EQUAL(item.second, 4);

  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
    ASSERT_EQUAL(strings.GetMax().second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
