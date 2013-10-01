//
// myAllocator.h
// 
//  Created on: Aug 4, 2013
//      Author: Manish Kumar
//

#ifndef MYALLOCATOR_H_
#define MYALLOCATOR_H_

#include <memory>
#include <new>
#include <typeinfo>

#include <glog/logging.h>


template<typename _Tp>
struct ObjAllocTraits {

  template<typename U>
  struct rebind {
    using other = ObjAllocTraits<U>;
  };

  inline explicit ObjAllocTraits() {}
  inline ~ObjAllocTraits() {};

  template<typename U>
  inline explicit ObjAllocTraits(ObjAllocTraits<U>&) {}

  // to get address
  inline _Tp* address(_Tp& r) {
    return &r;
  }

  inline _Tp* const address(_Tp const& r) {
    return &r;
  }

  // construct (this can be specialized for types)
  void construct(_Tp* p, const _Tp& t) {
    new(p) _Tp(t);
  }

  void destroy(_Tp* p) {
    p->~_Tp();
  }
};

// A very inefficient memory allocator

template<typename _Tp>
struct CustomAllocPolicy {
  using value_type      = _Tp;
  using pointer         = _Tp*;
  using const_pointer   = const _Tp*;
  using reference       = _Tp&;
  using const_reference = const _Tp&;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  template<typename U>
  struct rebind{
    using other = CustomAllocPolicy<U>;
  };

  inline explicit CustomAllocPolicy(){}
  inline ~CustomAllocPolicy(){}
  inline explicit CustomAllocPolicy(const CustomAllocPolicy&){}

  template<typename U>
  inline explicit CustomAllocPolicy(const CustomAllocPolicy<U>&){}

  inline pointer allocate(size_type knt, typename std::allocator<void>::const_pointer hint = 0) {
    if (knt > 0) {
      LOG(INFO) << "allocating " << knt << " object of type " << typeid(_Tp).name() << " , total size = " << (knt*sizeof(_Tp)) << std::endl;
      try {
        pointer ret = reinterpret_cast<pointer>(::operator new(knt*sizeof(_Tp)));
        return ret;
      } catch (...) {
        LOG(INFO) << "FAILED: allocating " << knt << " object of type " << typeid(_Tp).name() << " , total size = " << (knt*sizeof(_Tp)) << std::endl;
        //return nullptr;
        throw;
      }
    }

    return nullptr;
  }

  inline void deallocate(pointer p, size_type knt) {
    LOG(INFO) << "deallocating " << knt << " object of type " << typeid(_Tp).name() << " , total size = " << (knt*sizeof(_Tp)) << std::endl;
    try {
      ::operator delete(p);
    } catch (...) {
      LOG(INFO) << "FAILED: deallocating " << knt << " object of type " << typeid(_Tp).name() << " , total size = " << (knt*sizeof(_Tp)) << std::endl;
      throw;
    }
  }

  inline size_type max_size() const {
    return std::numeric_limits<int>::max();
  }
};


template<typename _Tp, typename Policy = CustomAllocPolicy<_Tp>, typename Traits = ObjAllocTraits<_Tp>>
class MyAllocator : public Policy, public Traits {
  private:

  using AllocationPolicy = Policy;
  using TTraits          = Traits;

//  typedef Policy   AllocationPolicy;
//  typedef Traits   TTraits;

  public:

  using size_type       = typename AllocationPolicy::size_type;
  using difference_type = typename AllocationPolicy::difference_type;
  using pointer         = typename AllocationPolicy::pointer;
  using const_pointer   = typename AllocationPolicy::const_pointer;
  using reference       = typename AllocationPolicy::reference;
  using const_reference = typename AllocationPolicy::const_reference;
  using value_type      = typename AllocationPolicy::value_type;

  template<typename U>
  struct rebind {
    //using other = MyAllocator<U, typename AllocationPolicy::rebind<U>::other, typename TTraits::rebind<U>::other>;
    //typedef MyAllocator<U, typename AllocationPolicy::rebind<U>::other, typename TTraits::rebind<U>::other> other;
  };

  inline explicit MyAllocator(){}
  inline ~MyAllocator(){}
  inline explicit MyAllocator(const MyAllocator& rhs) : Policy(rhs), Traits(rhs){}

  template<typename U>
  inline explicit MyAllocator(const MyAllocator<U>&) {}

};

template <typename T, typename R, typename A>
inline bool operator == (const MyAllocator<T,R,A>& lhs, const MyAllocator<T,R,A>& rhs) {
  return ::operator ==(static_cast<R&>(lhs), static_cast<R&>(rhs));
}
#endif /* MYALLOCATOR_H_ */
