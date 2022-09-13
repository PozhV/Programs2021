//============================================================================
// Name        : rw5_explore_key_words.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"
#include "profile.h"
#include <future>
#include<functional>
#include <map>
#include <string>
#include<sstream>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
	  for(const auto& x: other.word_frequences)
		  word_frequences[x.first] += x.second;
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats stat;
	string word;
	for(auto c: line)
	{
		if(c == ' ' && word.size() > 0)
		{
			auto it = key_words.find(word);
			if(it != key_words.end())
			{
				if(stat.word_frequences.count(*it) > 0)
					stat.word_frequences[*it]++;
				else stat.word_frequences[*it] = 1;
			}
			word.clear();
		}
		else{
			word += c;
		}
	}
	if(word.size() > 0)
	{
		auto it = key_words.find(word);
		if(it != key_words.end())
		{
			if(stat.word_frequences.count(*it) > 0)
				stat.word_frequences[*it]++;
			else stat.word_frequences[*it] = 1;
		}
	}
	return stat;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	Stats result;
	int cells_count = 4;
	int i = 0;
	vector<string> sstrings(cells_count);
	vector<stringstream> sstreams(cells_count);
	vector<future<Stats>> f(cells_count);
	for (string line; getline(input, line); ) {
		sstrings[i] += move(line);
		sstrings[i] += "\n";
		i = (i + 1) % cells_count;
	}
	for (int i = 0; i < cells_count; i++) {
			sstreams[i] = stringstream(move(sstrings[i]));
	}
	for (int i = 0; i < cells_count; i++) {
		f[i] = async(ExploreKeyWordsSingleThread, ref(key_words), ref(sstreams[i]));
	}
	for (auto& i: f) {
		result += i.get();
	}
	  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
