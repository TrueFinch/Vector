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
 public:
  // @formatter:off
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
  //@ formatter:on


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
  // Operators and assigment
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


  // Element access
  reference       at( size_type pos );
  const_reference at( size_type pos ) const;

  reference       operator[]( size_type pos );
  const_reference operator[]( size_type pos ) const;

  reference       front();
  const_reference front() const;

  reference       back();
  const_reference back() const;


  // Data access
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

  // Capacity
  bool      empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void      reserve( size_type new_cap );
  size_type capacity() const noexcept;
  void      shrink_to_fit();

  // Modifiers
  void clear() noexcept;

  iterator insert( const_iterator pos, const T& value );
  iterator insert( const_iterator pos, T&& value );
  iterator insert( const_iterator pos, size_type count, const T& value );
  template< class InputIt >
  iterator insert( const_iterator pos, InputIt first, InputIt last );
  iterator insert( const_iterator pos, std::initializer_list<T> ilist );

  template< class... Args >
  iterator emplace( const_iterator pos, Args&&... args );

  iterator erase( const_iterator pos );
  iterator erase( const_iterator first, const_iterator last );

  void push_back( const T& value );
  void push_back( T&& value );

  template< class... Args >
  reference emplace_back( Args&&... args );

  void pop_back();

  void resize( size_type count );
  void resize( size_type count, const value_type& value );

  void swap( Vector& other ) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value
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
  size_t other_size = other.size();
  this->reallocate(other_size);
  for (size_t i = 0; i < other_size; ++i) {
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


} //namespace truefinch template library