//
// objKeyManager.h
// 
//  Created on: Aug 14, 2013
//      Author: Manish Kumar
//

// openMPI, boost asio/c++11 network and libevent
// https://computing.llnl.gov/tutorials/mpi/
// http://blog.cloudera.com/blog/2009/08/hadoop-default-ports-quick-reference/
#if 0
#ifndef OBJKEYMANAGER_H_
#define OBJKEYMANAGER_H_

namespace mkTest {

template<typename _Tp = uint64_t>
class ObjKeyManager : private boost::noncopyable {
  public:

//  explicit ObjKeyManager() : mutex_(), key_() {}
  static std::shared_ptr<ObjKeyManager> getInstance() {
    if (!instance_) {
      instance_.reset(new ObjKeyManager);
    }
    return instance_;
  }

  _Tp nextKey() {
    std::lock lock(mutex_);
    return key_.next();
  }

  private:

  template <typename K>
  class key {
    typedef K key_type;

    public:

    explicit key(const key_type& k = key_type()) : __key(k) {}

    key_type next() {
      return ++__key;
    }

    key_type __key;
  };

  mutable std::mutex    mutex_;
  key<_Tp>              key_;

  static std::shared_ptr<ObjKeyManager> instance_;

};

}

#endif
#endif /* OBJKEYMANAGER_H_ */
