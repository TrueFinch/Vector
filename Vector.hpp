//
// Created by truefinch on 01.06.18.
//

#pragma once

#include <memory>
#include <vector>
#include "Iterator.hpp"

namespace tftl {
/**
 * @brief tftl::Vector is a sequence  container that encapsulates dynamic size arrays
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
  Vector() noexcept (noexcept(Allocator())) = default;
  explicit Vector( const Allocator& alloc ) noexcept;
  Vector( size_type count, const T& value, const Allocator& alloc = Allocator() );
  explicit Vector( size_type count, const Allocator& alloc = Allocator() );
  template< class InputIt >
  Vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
  Vector( const Vector& other );
  Vector( Vector&& other ) noexcept;
  Vector( Vector&& other, const Allocator& alloc );
  Vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() );

  ~Vector();

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

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const;


  // Data access
  T* data() noexcept;
  const T* data() const noexcept;

  // Iterators:
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  const_reverse_iterator crbegin() const noexcept;

  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crend() const noexcept;

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
};

// construct/copy/destroy:

} //namespace truefinch template library