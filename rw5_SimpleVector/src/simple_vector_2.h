/*
 * simple_vector_2.h
 *
 *  Created on: 15 окт. 2021 г.
 *      Author: User
 */

#ifndef SIMPLE_VECTOR_2_H_
#define SIMPLE_VECTOR_2_H_
#include <cstdint>
#include<utility>
using namespace std;
template <typename T>
class SimpleVector {
public:
  SimpleVector();
  SimpleVector(SimpleVector&& vec);
  SimpleVector& operator=(SimpleVector&& vec);
  explicit SimpleVector(size_t size);
  ~SimpleVector();
  T& operator[](size_t index);
  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;
  size_t Size() const;
  size_t Capacity() const;
  void PushBack(T value);
private:
  T* data;
  size_t capac;
  size_t size_;
};
template<class T>
SimpleVector<T>::SimpleVector(): data(nullptr), capac(0), size_(0){}
template<class T>
SimpleVector<T>::SimpleVector(SimpleVector&& vec): data(vec.data), capac(vec.capac), size_(vec.size_){
	  vec.data = nullptr;
	  vec.capac = 0;
	  vec.size_ = 0;
}
template<class T>
SimpleVector<T>::SimpleVector(size_t size){
	  data = new T[size];
	  capac = size;
	  size_ = size;
}
template<class T>
SimpleVector<T>::~SimpleVector(){
	  delete[] data;
}
template<class T>
T& SimpleVector<T>::operator[](size_t index){
	  return data[index];
}

template<class T>
T* SimpleVector<T>::begin(){
	  return data;
}
template<class T>
T* SimpleVector<T>::end(){
	  return data + size_;
}
template<class T>
const T* SimpleVector<T>::begin() const{
	  return data;
 }
template<class T>
const T* SimpleVector<T>::end() const{
	  return data + size_;
 }
template<class T>
size_t SimpleVector<T>::Size() const{
	  return size_;
}
template<class T>
size_t SimpleVector<T>::Capacity() const{
	  return capac;
}
template<class T>
void SimpleVector<T>::PushBack(T value){
	  if(capac == 0)
	  {
		  data = new T[1];
		  *data = move(value);
		  capac = 1;
		  size_ = 1;
	  }
	  else if(size_ == capac)
	  {
		  T* data_;
		  data_ = new T[2*capac];
		  for (size_t i = 0; i < capac; i++)
		               data_[i] = move(data[i]);
	      data_[size_] = move(value);
	      size_++;
	      delete[] data;
	      data = data_;
	      capac *= 2;
	  }
	  else{
		  data[size_] = move(value);
		  size_++;
	  }
}
template<class T>
SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector&& vec){
	  delete[] data;
	  size_ = vec.Size();
	  capac = vec.Capacity();
	  data = vec.data;
	  vec.data = nullptr;
	  vec.capac = 0;
	  vec.size_ = 0;
	  return *this;
}
#endif /* SIMPLE_VECTOR_2_H_ */
