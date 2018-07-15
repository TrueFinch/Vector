//
// Created by truefinch on 01.06.18.
//

#pragma once

#include <memory>
#include <vector>
#include "iterator.hpp"

namespace tftl {
/**
 * @brief tftl::Vector is a sequence container that encapsulates dynamic size arrays
 *
 * @tparam T The type of the elements.
 * @tparam Allocator An allocator that is used to acquire/release memory
 * and to construct/destroy the elements in that memory.
 * The type must meet the requirements of Allocator.
 * The behavior is undefined if Allocator::value_type is not the same as T.
 */
template<typename T, typename Allocator>
class vector;
} //namespace truefinch template library

template<typename T, typename Allocator>
bool operator==(const tftl::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator==(const tftl::vector<T, Allocator>& lhs, const tftl::vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const tftl::vector<T, Allocator>& lhs, const tftl::vector<T, Allocator>& rhs);

namespace tftl {
/**
 *
 * @tparam T
 * @tparam Allocator
 */
template<typename T, typename Allocator = std::allocator<T>>
class vector {
  // @formatter:off
 public:
  ///This is Member types
  typedef T                                      value_type;
  typedef Allocator                              allocator_type;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;
  typedef typename std::allocator_traits         <Allocator>::pointer pointer;
  typedef typename std::allocator_traits         <Allocator>::const_pointer const_pointer;
  typedef tftl::iterator <value_type>            iterator;
  typedef const tftl::iterator <value_type>      const_iterator;
  typedef std::reverse_iterator <iterator>       reverse_iterator;
  typedef std::reverse_iterator <const_iterator> const_reverse_iterator;

  // construct/copy/destroy:
  vector() noexcept ( noexcept(Allocator()) ) = default;
  explicit vector( const Allocator& alloc ) noexcept;
  vector( size_type count, const T& value, const Allocator& alloc = Allocator() );
  explicit vector( size_type count, const Allocator& alloc = Allocator()) ;
  template<typename InputIt, typename = typename std::enable_if <!std::is_integral <InputIt>::value>::type>
  vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
  vector( const vector& other );
  vector( vector&& other ) noexcept;
  vector( vector&& other, const Allocator& alloc );
  vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() );

  ~vector();

  // Operators and assignment:
  vector& operator=( const vector& other );
  vector& operator=(vector&& other) noexcept(
      std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
      || std::allocator_traits<Allocator>::is_always_equal::value);
  vector& operator=( std::initializer_list<T> ilist );

  void assign( size_type count, const T& value );
  template< class InputIt, class = typename std::enable_if <!std::is_integral <InputIt>::value>::type >
  void assign( InputIt first, InputIt last );
  void assign( std::initializer_list<T> ilist );

  allocator_type get_allocator() const;


  // Element access:
  reference       at( size_type pos );
  const_reference at( size_type pos ) const;

  reference       operator[]( size_type pos );
  const_reference operator[]( size_type pos ) const;

  reference       front();
  const_reference front() const;

  reference       back();
  const_reference back() const;


  // Data access:
  T*        data() noexcept;
  const T*  data() const noexcept;

  // Iterators:
  iterator                begin() noexcept;
  const_iterator          begin() const noexcept;
  const_iterator          cbegin() const noexcept;

  iterator                end() noexcept;
  const_iterator          end() const noexcept;
  const_iterator          cend() const noexcept;

  reverse_iterator        rbegin() noexcept;
  const_reverse_iterator  rbegin() const noexcept;
  const_reverse_iterator  crbegin() const noexcept;

  reverse_iterator        rend() noexcept;
  const_reverse_iterator  rend() const noexcept;
  const_reverse_iterator  crend() const noexcept;

  // Capacity:
  bool      empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void      reserve( size_type new_cap );
  size_type capacity() const noexcept;
  void      shrink_to_fit();

  // Modifiers:
  void clear() noexcept;

  iterator  insert( const_iterator pos, const T& value );
  iterator  insert( const_iterator pos, T&& value );
  iterator  insert( const_iterator pos, size_type count, const T& value );
  template< class InputIt, class = typename std::enable_if <!std::is_integral <InputIt>::value>::type >
  iterator  insert( const_iterator pos, InputIt first, InputIt last );
  iterator  insert( const_iterator pos, std::initializer_list<T> ilist );

  template< class... Args >
  iterator  emplace( const_iterator pos, Args&&... args );

  iterator  erase( const_iterator pos );
  iterator  erase( const_iterator first, const_iterator last );

  void      push_back( const T& value );
  void      push_back( T&& value );

  template< class... Args >
  reference emplace_back( Args&&... args );

  void      pop_back();

  void      resize( size_type count );
  void      resize( size_type count, const value_type& value );

  void      swap( vector& other ) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value
      || std::allocator_traits<Allocator>::is_always_equal::value);

 private:
  Allocator allocator_; // allocator TODO: replace by my own


  pointer head_ = nullptr; //Pointer to the first element of the vector
  pointer tail_ = nullptr; //Pointer to the past-the-last element of the vector
  pointer peak_ = nullptr; //Pointer to the end of available space of the vector

  const float vector_growth_factor_ = 2.0;

  // Methods to manipulate with memory by using allocator:
  void reallocate(size_type new_size);
  void init(iterator start, iterator finish);
  void deallocate(iterator start, iterator finish);

  // @formatter:on
};

// construct/copy/destroy:
template<typename T, typename Allocator>
vector<T, Allocator>::vector(const Allocator& alloc) noexcept {
  this->allocator_ = alloc;
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector::size_type count, const T& value, const Allocator& alloc) {
  this->assign(count, value);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector::size_type count, const Allocator& alloc) {
  this->reallocate( count );
  this->tail_ = this->head_ + count;
  this->init( this->begin(), this->end());
}

template<typename T, typename Allocator>
template<class InputIt, typename isIterator>
vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc) {
  this->assign(first, last);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other) {
  size_type other_size = other.size();
  this->reallocate(other_size);
  for (size_type i = 0; i < other_size; ++i) {
    this->allocator_.construct(this->head_ + i, other[i]);
  }
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
    : allocator_{other.allocator_}, head_{other.head_}, tail_{other.tail_}, peak_{other.tail_} {
  other.head_ = other.tail_ = other.peak_ = nullptr;
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other, const Allocator& alloc)
    : allocator_{alloc}, head_{other.head_}, tail_{other.tail_}, peak_{other.tail_} {
  other.head_ = other.tail_ = other.peak_ = nullptr;
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init, const Allocator& alloc) {
  assign(init.begin(), init.end());
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector() {
  this->deallocate(this->begin(), this->end());
  this->allocator_.deallocate(head_, this->capacity());
}

// Operators and assigment:
template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
  if (this != &other) {
    this->erase(this->begin(), this->end());
    if (other.size() > capacity()) {
      reallocate(other.size());
    }

    for (size_type i = 0; i < other.size(); ++i) {
      this->allocator_.construct(this->head_ + i, other[i]);
    }

    this->tail_ = this->head_ + other.size();
  }
  return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept(
std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
    || std::allocator_traits<Allocator>::is_always_equal::value) {
  if (this == &other) {
    return *this;
  }
  this->clear();
  this->swap(other);
  return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> ilist) {
  this->assign(ilist.begin(), ilist.end());
  return *this;
}

// Replaces the contents with count copies of value value
template<typename T, typename Allocator>
void vector<T, Allocator>::assign(vector::size_type count, const T& value) {
  this->erase(this->begin(), end());

  if (count > capacity()) {
    reallocate(count);
  }

  for (size_type i = 0; i < count; ++i) {
    allocator_.construct(this->head_ + i, value);
  }

  this->tail_ = this->head_ + count;
}

template<typename T, typename Allocator>
template<class InputIt, typename isIterator>
void vector<T, Allocator>::assign(InputIt first, InputIt last) {
  this->erase(this->begin(), this->end());
  typename vector<T, Allocator>::iterator::difference_type count = std::distance(first, last);

  if (this->capacity() < count) {
    this->reallocate(count);
  }

  for (auto it = this->begin(); first != last; ++it, ++first) {
    this->allocator_.construct(&*it, value_type(*first));
  }

  this->tail_ = this->head_ + count;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::assign(std::initializer_list<T> ilist) {
  this->assign(ilist.begin(), ilist.end());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const {
  return this->allocator_;
}

// Element access:
template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(vector::size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("tftl::vector::at: accessed element out of range");
  }
  return this->head_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(vector::size_type pos) const {
  if (pos >= this->size()) {
    throw std::out_of_range("tftl::vector::at: accessed element out of range");
  }
  return this->head_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](vector::size_type pos) {
  return this->head_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](vector::size_type pos) const {
  return this->head_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
  return *(this->head_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
  return *(this->head_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
  return *(--this->tail_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
  return *(this->tail_);
}

// Data access:
template<typename T, typename Allocator>
T* vector<T, Allocator>::data() noexcept {
  return this->head_;
}

template<typename T, typename Allocator>
const T* vector<T, Allocator>::data() const noexcept {
  return this->head_;
}

// Iterators:
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() noexcept {
  return tftl::vector<T, Allocator>::iterator(this->head_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const noexcept {
  return tftl::vector<T, Allocator>::const_iterator(this->head_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin() const noexcept {
  return tftl::vector<T, Allocator>::const_iterator(this->head_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() noexcept {
  return tftl::vector<T, Allocator>::iterator(this->tail_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const noexcept {
  return tftl::vector<T, Allocator>::const_iterator(this->tail_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cend() const noexcept {
  return tftl::vector<T, Allocator>::const_iterator(this->tail_);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() noexcept {
  return tftl::vector<T, Allocator>::reverse_iterator(this->head_ + this->size());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const noexcept {
  return tftl::vector<T, Allocator>::const_reverse_iterator(this->tail_ - 1);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crbegin() const noexcept {
  return tftl::vector<T, Allocator>::const_reverse_iterator(this->tail_ - 1);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() noexcept {
  return tftl::vector<T, Allocator>::reverse_iterator(this->head_ - 1);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const noexcept {
  return tftl::vector<T, Allocator>::const_reverse_iterator(this->head_ - 1);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crend() const noexcept {
  return tftl::vector<T, Allocator>::const_reverse_iterator(this->head_ - 1);
}

// Capacity:
template<typename T, typename Allocator>
bool vector<T, Allocator>::empty() const noexcept {
  return this->size() == 0;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const noexcept {
  return this->tail_ - this->head_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const noexcept {
  return static_cast<size_type>(SIZE_MAX / sizeof(T));
}

template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(vector::size_type new_cap) {
  if (new_cap > this->max_size()) {
    throw std::length_error("tftl::vector::reserve(): new_cap is too big, not enough memory to reserve");
  };
  if (new_cap > this->capacity()) {
    this->reallocate(new_cap);
  }
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const noexcept {
  return this->peak_ - this->head_;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
  this->reallocate(this->size());
}

// Modifier:
template<typename T, typename Allocator>
void vector<T, Allocator>::clear() noexcept {
  this->allocator_.deallocate(this->head_, this->capacity());
  this->head_ = this->tail_ = this->peak_ = nullptr;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, const T& value) {
  size_type index = pos - this->begin();
  if (size() + 1 > this->capacity()) {
    this->reallocate(size() + 1);
  }

  auto iter = this->begin() + index;
  std::copy_backward(iter, this->end(), iter + this->size() - index + 1);
  *iter = value;
  ++(this->tail_);
  return iter;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, T&& value) {
  size_type index = pos - this->begin();

  size_type new_size = this->size() + 1;
  if ((new_size) > this->capacity()) {
    this->reallocate(new_size);
  }

  auto iter = this->begin() + index;
  std::copy_backward(iter, this->end(), this->end() + 1);
  *iter = value;
  ++(this->tail_);
  return iter;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos,
                                                                     size_type count,
                                                                     const T& value) {
  size_type index = pos - begin();

  size_type new_size = size() + count;
  if (new_size > capacity()) {
    reallocate(new_size);
  }

  auto iter = begin() + index;
  std::copy_backward(iter, end(), end() + count);
  std::fill(iter, iter + count, value);
  this->tail_ = this->head_ + new_size;
  return iter;
}

template<typename T, typename Allocator>
template<class InputIt, typename isIterator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
  difference_type count = std::distance(first, last);
  size_type index = pos - this->begin();

  size_type new_size = this->size() + count;
  if (new_size > this->capacity()) {
    this->reallocate(new_size);
  }

  auto iter = this->begin() + index;
  std::copy_backward(iter, this->end(), this->end() + count);
  std::copy(first, last, iter);
  this->tail_ = this->head_ + new_size;
  return iter;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos,
                                                                     std::initializer_list<T> ilist) {
  return this->insert(pos, ilist.begin(), ilist.end());
}

template<typename T, typename Allocator>
template<class... Args>
typename vector<T, Allocator>::iterator vector<T, Allocator>::emplace(const_iterator pos, Args&& ... args) {
  size_type index = pos - this->begin();

  size_type new_size = this->size() + 1;
  if (new_size > this->capacity()) {
    this->reallocate(new_size);
  }

  auto iter = this->begin() + index;
  std::copy_backward(iter, this->end(), ++(this->tail_));
  allocator_.construct(&*iter, std::forward<Args>(args)...);
  return iter;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator pos) {
  allocator_.destroy(&*pos);
  std::copy(pos + 1, this->end(), pos);
  --(this->tail_);
  return pos;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
  for (auto it = first; it != last; ++it) {
    allocator_.destroy(&*it);
  }

  if (this->end() > (last + 1)) {
    std::copy(last + 1, this->end(), first + 1);
  }

  this->tail_ -= std::distance(first, last);
  return first;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value) {
  size_type new_size = this->size() + 1;
  if (new_size >= this->capacity()) {
    this->reallocate(new_size);
  }
  allocator_.construct(this->tail_++, T(value));
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(T&& value) {
  size_type new_size = this->size() + 1;
  if (new_size >= this->capacity()) {
    this->reallocate(new_size);
  }
  std::swap(*(this->tail_++), value);
}

template<typename T, typename Allocator>
template<class... Args>
typename vector<T, Allocator>::reference vector<T, Allocator>::emplace_back(Args&& ... args) {
  emplace(this->end(), std::forward<Args>(args)...);
  return *(this->tail_);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
  allocator_.destroy((this->tail_)--);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::resize(vector::size_type count) {
  size_type index = this->size();
  if (count > this->capacity()) {
    this->reallocate(count);
  }

  this->tail_ = this->head_ + count;
  if (index < this->size()) {
    this->init(this->begin() + index, this->end());
  } else {
    this->deallocate(this->end(), this->begin() + index);
  }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count, const value_type& value) {
  size_type prev_size = size();
  resize(count);
  if (count <= prev_size) {
    return;
  }

  for (size_type i = prev_size; i < count; ++i) {
    allocator_.construct(this->head_ + i, value);
  }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept(
std::allocator_traits<Allocator>::propagate_on_container_swap::value
    || std::allocator_traits<Allocator>::is_always_equal::value) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->peak_, other.peak_);
  std::swap(this->allocator_, other.allocator_);
}

// Methods to manipulate with memory by using allocator:
template<typename T, typename Allocator>
void vector<T, Allocator>::reallocate(size_type new_size) {
  if (new_size >= capacity()) {
    new_size *= this->vector_growth_factor_;
  }

  pointer new_begin = this->allocator_.allocate(new_size);
  if (new_begin == this->head_) {
    return;
  }

  if (!std::is_null_pointer<decltype(this->head_)>()) {
    try {
      std::copy(this->head_, this->head_ + std::min(this->size(), new_size), new_begin);
    } catch (...) {
      this->allocator_.deallocate(new_begin, new_size);
      throw std::range_error("tftl::vector::reallocate: invalid memory copy");
    }
    this->allocator_.deallocate(this->head_, this->capacity());
  }

  this->tail_ = new_begin + size();
  this->head_ = new_begin;
  this->peak_ = new_begin + new_size;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::init(iterator start, iterator finish) {
  for (auto it = start; it != finish; ++it) {
    this->allocator_.construct(&*it, value_type());
  }
}

template<typename T, typename Allocator>
void vector<T, Allocator>::deallocate(iterator start, iterator finish) {
  for (auto it = start; it != finish; ++it) {
    this->allocator_.destroy(&*it);
  }
}

} //namespace truefinch template library

// Operators
template<typename T, typename Allocator>
bool operator==(const tftl::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (auto i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

template<typename T, typename Allocator>
bool operator==(const tftl::vector<T, Allocator>& lhs, const tftl::vector<T, Allocator>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (auto i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

template<typename T, typename Allocator>
bool operator<(const tftl::vector<T, Allocator>& lhs, const tftl::vector<T, Allocator>& rhs) {
  return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
//  if (lhs.size() == rhs.size()) {
//    return false;
//  }
//
//  for (auto i = 0; i < lhs.size(); ++i) {
//    if (lhs[i] >= rhs[i]) {
//      return false;
//    }
//  }
//
//  return true;
};