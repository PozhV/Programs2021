/*
 * stack_vector.h
 *
 *  Created on: 2 окт. 2021 г.
 *      Author: User
 */
#pragma once
#include<array>
#include<iterator>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0){
	  if(a_size > N)
	  {
		  throw invalid_argument(" ");
	  }
	  size = a_size;
	  capacity = N;
  }

  T& operator[](size_t index){
	  return vec_stack[index];
  }
  const T& operator[](size_t index) const{
	  return vec_stack[index];
  }
  auto begin(){
	  return vec_stack.begin();
  }
  auto end(){
	  return vec_stack.begin()+size;
  }
  const auto begin() const
  {
	  return vec_stack.begin();
  }
  const auto end() const{
	  return vec_stack.begin()+size;
  }
  size_t Size() const{
	  return size;
  }
  size_t Capacity() const{
	  return capacity;
  }
  void PushBack(const T& value){
	  if(capacity == size)
	  {
		  throw overflow_error(" ");
	  }
	  else{
		  vec_stack[size] = value;
		  size++;
	  }
  }
  T PopBack(){
	  if(size == 0)
	  {
		throw underflow_error(" ");
	  }
	  else{
	  size--;
	  }
	  return vec_stack[size];
  }

private:
  array<T, N> vec_stack;
  size_t size;
  size_t capacity;
};
