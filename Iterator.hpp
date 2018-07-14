//
// Created by truefinch on 05.06.18.
//

#pragma once

#include <memory>

namespace tftl {
template<typename T>
class Iterator;
} // namespace truefinch template library

//Do redefine for std algorithms compatibility
namespace std {
template<typename T>
struct Iterator_traits<tftl::Iterator<T>> {
  // @formatter:off
  typedef std::ptrdiff_t                  difference_type;
  typedef T                               value_type;
  typedef T*                              pointer;
  typedef T&                              reference;
  typedef std::random_access_iterator_tag iterator_category;
  // @formatter:on
};
}

namespace tftl {
template<typename T>
class Iterator {
 public:
  // @formatter:off
  typedef typename std::Iterator_traits <Iterator <T>> traits;
  typedef typename traits::difference_type             difference_type;
  typedef typename traits::value_type                  value_type;
  typedef typename traits::pointer                     pointer;
  typedef typename traits::reference                   reference;
  typedef typename traits::iterator_category           iterator_category;
  //@ formatter:on

  //constructors
  explicit Iterator(pointer ptr = nullptr) : pointer_( ptr ) {};

  Iterator(const Iterator& other) {};

  Iterator&      operator=(const Iterator&);
  Iterator&      operator++();
  Iterator&      operator--();
  const Iterator operator++(int);
  const Iterator operator--(int);
  Iterator&      operator+=(difference_type);
  Iterator&      operator-=(difference_type);

  difference_type operator-(const Iterator&) const;
  Iterator        operator+(difference_type) const;
  Iterator        operator-(difference_type) const;

  reference operator*() const;
  pointer   operator->() const;
  reference operator[](difference_type) const;

  bool operator==(const Iterator&) const;
  bool operator!=(const Iterator&) const;
  bool operator>(const Iterator&) const;
  bool operator<(const Iterator&) const;
  bool operator>=(const Iterator&) const;
  bool operator<=(const Iterator&) const;

 private:
  pointer pointer_;
};
template <typename T>
Iterator <T>& Iterator <T>::operator=(const Iterator& other)
{
  pointer_ = other.pointer_;
  return *this;
}

template <typename T>
Iterator <T>& Iterator <T>::operator++()
{
  ++pointer_;
  return *this;
}

template <typename T>
Iterator <T>& Iterator <T>::operator--()
{
  --pointer_;
  return *this;
}

template <typename T>
const Iterator <T> Iterator <T>::operator++(int)
{
  Iterator& foo( *this );
  ++pointer_;
  return foo;
}

template <typename T>
const Iterator <T> Iterator <T>::operator--(int)
{
  Iterator foo( *this );
  --pointer_;
  return foo;
}

template <typename T>
Iterator <T>& Iterator <T>::operator+=(difference_type n)
{
  pointer_ += n;
  return *this;
}

template <typename T>
Iterator <T>& Iterator <T>::operator-=(difference_type n)
{
  pointer_ -= n;
  return *this;
}

template <typename T>
typename Iterator <T>::difference_type Iterator <T>::operator-(const Iterator& other) const
{
  return pointer_ - other.pointer_;
}

template <typename T>
Iterator <T> Iterator <T>::operator+(difference_type n) const
{
  return Iterator( pointer_ + n );
}

template <typename T>
Iterator <T> Iterator <T>::operator-(difference_type n) const
{
  return Iterator( pointer_ - n );
}

template <typename T>
typename Iterator <T>::reference Iterator <T>::operator[](difference_type i) const
{
  return pointer_[i];
}

template <typename T>
typename Iterator <T>::reference Iterator <T>::operator*() const
{
  return *pointer_;
}

template <typename T>
typename Iterator <T>::pointer Iterator <T>::operator->() const
{
  return pointer_;
}

template <typename T>
bool Iterator <T>::operator==(const Iterator& other) const
{
  return pointer_ == other.pointer_;
}

template <typename T>
bool Iterator <T>::operator!=(const Iterator& other) const
{
  return !(*this == other);
}

template <typename T>
bool Iterator <T>::operator<=(const Iterator& other) const
{
  return pointer_ <= other.pointer_;
}

template <typename T>
bool Iterator <T>::operator>=(const Iterator& other) const
{
  return pointer_ >= other.pointer_;
}

template <typename T>
bool Iterator <T>::operator<(const Iterator& other) const
{
  return pointer_ < other.pointer_;
}

template <typename T>
bool Iterator <T>::operator>(const Iterator& other) const
{
  return pointer_ > other.pointer_;
}
} //namespace truefinch template library
