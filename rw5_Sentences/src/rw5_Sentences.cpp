//============================================================================
// Name        : rw5_Sentences.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	size_t i = 0;
	vector<Sentence<Token>> sentences;
	for(auto it = tokens.begin(); it != tokens.end(); it++)
	{
		if(i == sentences.size() && !it->IsEndSentencePunctuation())
			sentences.resize(i+1);
		else if(i == sentences.size())
		{
			if(i == 0)
				sentences.resize(i+1);
			else
				i--;
		}
		if(it->IsEndSentencePunctuation())
		{
			sentences[i].push_back(move(*it));
			i++;
		}
		else sentences[i].push_back(move(*it));
	}
	return sentences;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"!", true}}, {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
