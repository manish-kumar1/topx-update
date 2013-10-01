//
// object.hpp
// Copyright 2013, 2014 Manish Kumar (manish.iitgcse@gmail.com)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Sep 11, 2013
//      Author: Manish Kumar
//

#ifndef OBJECT_H_
#define OBJECT_H_

//#include <mutex>
//#include <exception>
//#include <iterator>
//#include <memory>

//#include "objIterator.hpp"

//#include "debug.h"

namespace mkTest {

// TODO:
// 1. define a object
// 2. its allocator
// 3. an iterator for it

struct Object {

  virtual ~Object() {}
};

#if 0
template<
         typename _Tp,
         typename _Iterator = object_iterator<_Tp>,
         typename _Alloc    = std::allocator <_Tp>
        >
class Object {
    public:
    using ObjectKeyType = typename uint64_t;

    Object(_Iterator& itr = _Iterator()
         , _Alloc& alloc = _Alloc()
#ifndef NDEBUG
         ,
         mkTest::debug::DebugObject* dobj = new mkTest::debug::DebugObject()
#endif
    ) :
      iterator_(itr),
      alloc_(alloc),
      mutex_(std::mutex())
    {
#ifndef NDEBUG
      uniqueKey_ = mkTest::ObjKeyManager::getInstance()->nextKey();
      dobj_->reset(dobj);
      dobj_->attach(uniqueKey_);
#endif
    }

    virtual ~Object() = 0;

    // for debugging purpose
#ifndef NDEBUG
    std::unique_ptr<mkTest::debug::DebugObject> dobj_;
    ObjectKeyType  uniqueKey_;
#endif

    private:

    mutable std::mutex mutex_;

    _Iterator iterator_;
    _Alloc    alloc_;
};
#endif
}

#endif /* OBJECT_HPP_ */
