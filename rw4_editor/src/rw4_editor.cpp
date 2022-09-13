//============================================================================
// Name        : rw4_editor.cpp
// Author      : Vsevolod Pozhalostin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <string_view>
#include<iterator>
#include <list>
#include <string>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  Editor()
  {
	  pos = chars.begin();
  }
  void Left(){
	  pos != chars.begin() ? pos-- : pos;
  }
  void Right(){
	  pos != chars.end() ? pos++ : pos;
  }
  void Insert(char token){
	  pos = chars.insert(pos, token);
	  pos++;
  }
  void Cut(size_t tokens = 1){
	  buffer.clear();
	  auto it = buffer.begin();
	  while((pos != chars.end()) && (tokens > 0))
	  {
		  tokens--;
		  it = buffer.insert(it, *pos);
		  it++;
		  pos = chars.erase(pos);
	  }
  }
  void Copy(size_t tokens = 1){
	  buffer.clear();
	  auto it =buffer.begin();
	  auto pos_ = pos;
	  while((pos_ != chars.end()) && (tokens > 0))
	  {
		  tokens--;
		  it = buffer.insert(it, *pos_);
		  it++;
		  pos_++;
	  }
  }
  void Paste(){
	  chars.insert(pos, buffer.begin(), buffer.end());
  }
  string GetText() const{
	  string s;
	  for(auto it: chars)
	  {
		  s += it;
	  }
	  return s;
  }
  string GetBuffer() const{
	  string s;
	  for(auto it: buffer)
	  {
		  s += it;
	  }
	  return s;
  }
  list<char>::iterator pos;
  list<char> chars;
  list<char> buffer;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    ASSERT_EQUAL(editor.GetText(), "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    ASSERT_EQUAL(editor.GetText(), "world");
    ASSERT_EQUAL(editor.GetBuffer(), "hello, ");
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
