/*
 * simple_vector.h
 *
 *  Created on: 14 ���. 2021 �.
 *      Author: User
 */

#ifndef SIMPLE_VECTOR_H_
#define SIMPLE_VECTOR_H_
#pragma once
#include <cstdlib>
#include<algorithm>
// � еализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(): data(nullptr), capac(0), size_(0){}
  SimpleVector(const SimpleVector& vec): data(new T[vec.capac]), capac(vec.capac), size_(vec.size_){
	  std::copy(vec.begin(), vec.end(), begin());
  }
  explicit SimpleVector(size_t size){
	  data = new T[size];
	  capac = size;
	  size_ = size;
  }
  ~SimpleVector(){
	  delete[] data;
  }

  T& operator[](size_t index){
	  return data[index];
  }

  T* begin(){
	  return data;
  }
  T* end(){
	  return data + size_;
  }
  const T* begin() const{
 	  return data;
   }
   const T* end() const{
 	  return data + size_;
   }

  size_t Size() const{
	  return size_;
  }
  size_t Capacity() const{
	  return capac;
  }
  void PushBack(const T& value){
	  if(capac == 0)
	  {
		  data = new T[1];
		  *data = value;
		  capac = 1;
		  size_ = 1;
	  }
	  else if(size_ == capac)
	  {
		  T* data_;
		  data_ = new T[2*capac];
		  for (size_t i = 0; i < capac; i++)
		               *(data_ + i) = *(data + i);
	      data_[size_] = value;
	      size_++;
	      delete[] data;
	      data = data_;
	      capac *= 2;
	  }
	  else{
		  data[size_] = value;
		  size_++;
	  }
  }
  SimpleVector& operator=(const SimpleVector& vec){
	  delete[] data;
	  size_=vec.Size();
	  capac = vec.Capacity();
	  data = new T[capac];
	  std::copy(vec.begin(), vec.end(), begin());
	  return *this;
  }
private:
  T* data;
  size_t capac;
  size_t size_;
};

#endif /* SIMPLE_VECTOR_H_ */
