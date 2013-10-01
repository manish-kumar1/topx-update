//
// traits.h
// 
//  Created on: Aug 5, 2013
//      Author: Manish Kumar
//
#if 0
#ifndef OBJITERATOR_H_
#define OBJITERATOR_H_

#include <iterator>

#include "object.hpp"

namespace mkTest {

// XXX: traits
// http://www.generic-programming.org/languages/cpp/techniques.php
// http://gee.cs.oswego.edu/dl/oosdw3/ch25.html
// http://www.cantrip.org/cpp.html
// http://accu.org/index.php/journals/442
//
// XXX: efficiency
// http://en.wikibooks.org/wiki/Optimizing_C%2B%2B
//

// for iterator, define its iterator_traits (5 values like ::iterator_category, ::iterator::value_type, difference_type, pointer, referece)

// struct _Object_iterator : public std::iterator<std::bidirectional_iterator_tag, __Object> {};

//template<typename T, typename U>
//struct object_iterator;

template<typename _Iterator>
struct object_iterator_traits : public std::iterator_traits<_Iterator>
{
//  typedef std::random_access_iterator_tag   iterator_category;
  static int next(const std::vector<int>& num, size_t seq) {
    return num[seq];
  }
};

template<> struct object_iterator_traits<void> {
  static int next(const std::vector<int>& num, size_t seq) {
    throw std::logic_error("object_iterator_traits<void> shouldn't be used.");
  }
};

struct summed_iterator_tag {};
template<> struct object_iterator_traits<summed_iterator_tag> {
  static int next(const std::vector<int>& num, size_t seq) {
    return std::accumulate(num.begin(), num.begin()+seq, 0);
  }
};

template<class _Tp, class _Traits = object_iterator_traits<_Tp>>
struct object_iterator : public std::iterator<std::bidirectional_iterator_tag, _Tp>
{
  object_iterator(const std::vector<int>& numbers, size_t seq) : num_(numbers), seq_(seq) {}
  object_iterator(const object_iterator<_Tp, _Traits>& rhs) {
    num_ = rhs.num_;
    seq_ = rhs.seq_;
  }

  const int operator *() const {
    return _Traits::next(num_, seq_);
  }

  object_iterator& operator ++(int) {
    ++seq_;
    return *this;
  }

  template<typename T>
  bool operator == (const object_iterator<T>& rhs) {
    return rhs.seq_ == seq_;
  }

  private:
  std::vector<int> num_;
  size_t seq_;
};

//template<typename _Tp>
//struct __Object_iterator_traits {
//    typedef std::bidirectional_iterator_tag iterator_category;
//    typedef _Tp                             value_type;
//    typedef std::ptrdiff_t                  difference_type;
//    typedef _Tp*                            pointer;
//    typedef _Tp&                            reference;
//};
//
//template<typename _Tp>
//struct __Object_const_iterator_traits {
//    typedef std::bidirectional_iterator_tag iterator_category;
//    typedef _Tp                             value_type;
//    typedef std::ptrdiff_t                  difference_type;
//    typedef const _Tp*                      pointer;
//    typedef const _Tp&                      reference;
//};

//typedef __Object_iterator_traits<Object>  objIterTraits;

#endif
#endif /* OBJITERATOR_H_ */
