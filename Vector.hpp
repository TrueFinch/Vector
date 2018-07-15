//
// Created by truefinch on 01.06.18.
//

#pragma once

#include <memory>
#include <vector>
#include "Iterator.hpp"

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
class Vector;
} //namespace truefinch template library

template<typename T, typename Allocator>
bool operator==(const tftl::Vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator==(const tftl::Vector<T, Allocator>& lhs, const tftl::Vector<T, Allocator>& rhs);

namespace tftl {
/**
 *
 * @tparam T
 * @tparam Allocator
 */
template<typename T, typename Allocator = std::allocator<T>>
class Vector {
  // @formatter:off
 public:
  ///This is Member types
  typedef T                                                           value_type;
  typedef Allocator                                                   allocator_type;
  typedef std::size_t                                                 size_type;
  typedef std::ptrdiff_t                                              difference_type;
  typedef value_type&                                                 reference;
  typedef const value_type&                                           const_reference;
  typedef typename std::allocator_traits<Allocator>::pointer          pointer;
  typedef typename std::allocator_traits<Allocator>::const_pointer    const_pointer;
  typedef tftl::Iterator <value_type>                                 iterator;
  typedef const tftl::Iterator <value_type>                           const_iterator;
  typedef std::reverse_iterator <iterator>                            reverse_iterator;
  typedef std::reverse_iterator <const_iterator>                      const_reverse_iterator;

  // construct/copy/destroy:
  Vector() noexcept ( noexcept(Allocator()) ) = default;
  explicit Vector( const Allocator& alloc ) noexcept;
  Vector( size_type count, const T& value, const Allocator& alloc = Allocator() );
  explicit Vector( size_type count, const Allocator& alloc = Allocator()) ;
  template<class InputIt>
  Vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
  Vector( const Vector& other );
  Vector( Vector&& other ) noexcept;
  Vector( Vector&& other, const Allocator& alloc );
  Vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() );

  ~Vector();

  // Operators and assignment:
  Vector& operator=( const Vector& other );
  Vector& operator=(Vector&& other) noexcept(
      std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
      || std::allocator_traits<Allocator>::is_always_equal::value);
  Vector& operator=( std::initializer_list<T> ilist );

  void assign( size_type count, const T& value );
  template< class InputIt >
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
  template< class InputIt >
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

  void      swap( Vector& other ) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value
      || std::allocator_traits<Allocator>::is_always_equal::value);

 private:
  Allocator allocator_; // allocator TODO: replace by my own


  pointer head_ = nullptr; //Pointer to the first element of the Vector
  pointer tail_ = nullptr; //Pointer to the past-the-last element of the Vector
  pointer peak_ = nullptr; //Pointer to the end of available space of the Vector

  const float vector_growth_factor_ = 2.0;

  //Methods to manipulate with memory by using allocator
  void reallocate(size_type new_size);
  void init(iterator start, iterator finish);
  void deallocate(iterator start, iterator finish);

  // @formatter:on
};

// construct/copy/destroy:
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator& alloc) noexcept {//TODO
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector::size_type count, const T& value, const Allocator& alloc) {
  this->assign(count, value);
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector::size_type count, const Allocator& alloc) {

}

template<typename T, typename Allocator>
template<class InputIt>
Vector<T, Allocator>::Vector(InputIt first, InputIt last, const Allocator& alloc) {
  this->assign(first, last);
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other) {
  size_type other_size = other.size();
  this->reallocate(other_size);
  for (size_type i = 0; i < other_size; ++i) {
    this->allocator_.construct(this->head_ + i, other[i]);
  }
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other) noexcept
    : allocator_{other.allocator_}, head_{other.head_}, tail_{other.tail_}, peak_{other.tail_} {
  other.head_ = other.tail_ = other.peak_ = nullptr;
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other, const Allocator& alloc)
    : allocator_{alloc}, head_{other.head_}, tail_{other.tail_}, peak_{other.tail_} {
  other.head_ = other.tail_ = other.peak_ = nullptr;
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init, const Allocator& alloc) {
  assign(init.begin(), init.end());
}

template<typename T, typename Allocator>
Vector<T, Allocator>::~Vector() {
  this->deallocate(this->begin(), this->end());
  this->allocator_.deallocate(head_, this->capacity());
}

// Operators and assigment
template<typename T, typename Allocator>
Vector& Vector<T, Allocator>::operator=(const Vector& other) {
  if (this != &other) {
    this->erase(this->begin(), this->end());
    if (other.size() > capacity()) {
      reallocate(other.size());
    }

    for (size_type i = 0; i < other.size(); ++i) {
      this->allocator_.construct(this->head_ + i, other[i]);
    }

    this->peak_ = this->head_ + other.size();
  }
  return *this;
}

template<typename T, typename Allocator>
Vector& Vector<T, Allocator>::operator=(Vector&& other) noexcept(
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
Vector& Vector<T, Allocator>::operator=(std::initializer_list<T> ilist) {
  this->assign(ilist.begin(), ilist.end());
  return *this;
}

// Replaces the contents with count copies of value value
template<typename T, typename Allocator>
void Vector<T, Allocator>::assign(Vector::size_type count, const T& value) {
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
template<class InputIt>
void Vector<T, Allocator>::assign(InputIt first, InputIt last) {
  this->erase(this->begin(), this->end());
  typename iterator::difference_type count = labs(std::distance(first, last));

  if (this->capacity() < count) {
    this->reallocate(count);
  }

  for (auto it = this->begin(); first != last; ++it, ++first) {
    this->allocator_.construct(&*it, value_type(*first));
  }

  this->tail_ = this->head_ + count;
}

template<typename T, typename Allocator>
void Vector<T, Allocator>::assign(std::initializer_list<T> ilist) {
  this->assign(ilist.begin(), ilist.end());
}

template<typename T, typename Allocator>
allocator_type Vector<T, Allocator>::get_allocator() const {
  return this->allocator_;
}

// Element access
template<typename T, typename Allocator>
reference Vector<T, Allocator>::at(Vector::size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("tftl::Vector::at: accessed element out of range");
  }
  return this->head_[pos];
}

template<typename T, typename Allocator>
const_reference Vector<T, Allocator>::at(Vector::size_type pos) const {
  if (pos >= this->size()) {
    throw std::out_of_range("tftl::Vector::at: accessed element out of range");
  }
  return this->head_[pos];
}

template<typename T, typename Allocator>
reference Vector<T, Allocator>::operator[](Vector::size_type pos) {
  return this->head_[pos];
}

template<typename T, typename Allocator>
const_reference Vector<T, Allocator>::operator[](Vector::size_type pos) const {
  return this->head_[pos];
}

template<typename T, typename Allocator>
reference Vector<T, Allocator>::front() {
  return *(this->head_);
}

template<typename T, typename Allocator>
const_reference Vector<T, Allocator>::front() const {
  return *(this->head_);
}

template<typename T, typename Allocator>
reference Vector<T, Allocator>::back() {
  return *(this->tail_);
}

template<typename T, typename Allocator>
const_reference Vector<T, Allocator>::back() const {
  return *(this->tail_);
}

// Data access
template<typename T, typename Allocator>
T* Vector<T, Allocator>::data() noexcept {
  return head_;
}

template<typename T, typename Allocator>
const T* Vector<T, Allocator>::data() const noexcept {
  return head_;
}

// Iterators
template<typename T, typename Allocator>
Vector::iterator Vector<T, Allocator>::begin() noexcept {
  return tftl::Vector::iterator(this->head_);
}

template<typename T, typename Allocator>
Vector::const_iterator Vector<T, Allocator>::begin() const noexcept {
  return tftl::Vector::const_iterator(this->head_);
}

template<typename T, typename Allocator>
Vector::const_iterator Vector<T, Allocator>::cbegin() const noexcept {
  return tftl::Vector::const_iterator(this->head_);
}

template<typename T, typename Allocator>
Vector::iterator Vector<T, Allocator>::end() noexcept {
  return tftl::Vector::iterator(this->tail_);
}

template<typename T, typename Allocator>
Vector::const_iterator Vector<T, Allocator>::end() const noexcept {
  return tftl::Vector::const_iterator(this->tail_);
}

template<typename T, typename Allocator>
Vector::const_iterator Vector<T, Allocator>::cend() const noexcept {
  return tftl::Vector::const_iterator(this->tail_);
}

template<typename T, typename Allocator>
Vector::reverse_iterator Vector<T, Allocator>::rbegin() noexcept {
  return tftl::Vector::reverse_iterator(this->head_ + this->size());
}

template<typename T, typename Allocator>
Vector::const_reverse_iterator Vector<T, Allocator>::rbegin() const noexcept {
  return tftl::Vector::const_reverse_iterator(this->tail_ - 1);
}

template<typename T, typename Allocator>
Vector::const_reverse_iterator Vector<T, Allocator>::crbegin() const noexcept {
  return tftl::Vector::const_reverse_iterator(this->tail_ - 1);
}

template<typename T, typename Allocator>
Vector::reverse_iterator Vector<T, Allocator>::rend() noexcept {
  return tftl::Vector::reverse_iterator(this->head_ - 1);
}

template<typename T, typename Allocator>
Vector::const_reverse_iterator Vector<T, Allocator>::rend() const noexcept {
  return tftl::Vector::const_reverse_iterator(this->head_ - 1);
}

template<typename T, typename Allocator>
Vector::const_reverse_iterator Vector<T, Allocator>::crend() const noexcept {
  return tftl::Vector::const_reverse_iterator(this->head_ - 1);
}

} //namespace truefinch template library