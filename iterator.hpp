//
// Created by truefinch on 05.06.18.
//

#pragma once

#include <memory>

namespace tftl {
template<typename T>
class iterator;
} // namespace truefinch template library

//Do redefine for std algorithms compatibility
namespace std {
template<typename T>
struct iterator_traits<tftl::iterator<T>> {
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
class iterator {
 public:
  // @formatter:off
  typedef typename std::iterator_traits <iterator <T>> traits;
  typedef typename traits::difference_type             difference_type;
  typedef typename traits::value_type                  value_type;
  typedef typename traits::pointer                     pointer;
  typedef typename traits::reference                   reference;
  typedef typename traits::iterator_category           iterator_category;
  //@ formatter:on

  //constructors
  explicit iterator(pointer ptr = nullptr) : pointer_( ptr ) {};

  iterator(const iterator& other) : pointer_{other.pointer_} {};

  iterator&      operator=(const iterator&);
  iterator&      operator++();
  iterator&      operator--();
  const iterator operator++(int);
  const iterator operator--(int);
  iterator&      operator+=(difference_type);
  iterator&      operator-=(difference_type);

  difference_type operator-(const iterator&) const;
  iterator        operator+(difference_type) const;
  iterator        operator-(difference_type) const;

  reference operator*() const;
  pointer   operator->() const;
  reference operator[](difference_type) const;

  bool operator==(const iterator&) const;
  bool operator!=(const iterator&) const;
  bool operator>(const iterator&) const;
  bool operator<(const iterator&) const;
  bool operator>=(const iterator&) const;
  bool operator<=(const iterator&) const;

 private:
  pointer pointer_;
};
template <typename T>
iterator <T>& iterator <T>::operator=(const iterator& other)
{
  pointer_ = other.pointer_;
  return *this;
}

template <typename T>
iterator <T>& iterator <T>::operator++()
{
  ++pointer_;
  return *this;
}

template <typename T>
iterator <T>& iterator <T>::operator--()
{
  --pointer_;
  return *this;
}

template <typename T>
const iterator <T> iterator <T>::operator++(int)
{
  iterator& foo( *this );
  ++pointer_;
  return foo;
}

template <typename T>
const iterator <T> iterator <T>::operator--(int)
{
  iterator foo( *this );
  --pointer_;
  return foo;
}

template <typename T>
iterator <T>& iterator <T>::operator+=(difference_type n)
{
  pointer_ += n;
  return *this;
}

template <typename T>
iterator <T>& iterator <T>::operator-=(difference_type n)
{
  pointer_ -= n;
  return *this;
}

template <typename T>
typename iterator <T>::difference_type iterator <T>::operator-(const iterator& other) const
{
  return pointer_ - other.pointer_;
}

template <typename T>
iterator <T> iterator <T>::operator+(difference_type n) const
{
  return iterator( pointer_ + n );
}

template <typename T>
iterator <T> iterator <T>::operator-(difference_type n) const
{
  return iterator( pointer_ - n );
}

template <typename T>
typename iterator <T>::reference iterator <T>::operator[](difference_type i) const
{
  return pointer_[i];
}

template <typename T>
typename iterator <T>::reference iterator <T>::operator*() const
{
  return *pointer_;
}

template <typename T>
typename iterator <T>::pointer iterator <T>::operator->() const
{
  return pointer_;
}

template <typename T>
bool iterator <T>::operator==(const iterator& other) const
{
  return pointer_ == other.pointer_;
}

template <typename T>
bool iterator <T>::operator!=(const iterator& other) const
{
  return !(*this == other);
}

template <typename T>
bool iterator <T>::operator<=(const iterator& other) const
{
  return pointer_ <= other.pointer_;
}

template <typename T>
bool iterator <T>::operator>=(const iterator& other) const
{
  return pointer_ >= other.pointer_;
}

template <typename T>
bool iterator <T>::operator<(const iterator& other) const
{
  return pointer_ < other.pointer_;
}

template <typename T>
bool iterator <T>::operator>(const iterator& other) const
{
  return pointer_ > other.pointer_;
}
} //namespace truefinch template library
