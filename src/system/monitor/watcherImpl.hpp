//
// watcherImpl.hpp
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
//	This software is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Sep 8, 2013
//      Author: Manish Kumar
//

#ifndef WATCHERIMPL_HPP_
#define WATCHERIMPL_HPP_

#include <memory>

#include "watcher.hpp"

#include "../core/object.hpp"
#include "../core/runnable.hpp"

namespace mkTest { namespace system {

// this contains all information about actions
// happened on the object
struct WatchResult{
  virtual ~WatchResult() {}
};

struct ObjectActionListner {
  virtual void handleWatchResult(std::shared_ptr<Object>& obj, std::shared_ptr<WatchResult>& result) = 0;

};

struct WatchMetaData {
  explicit WatchMetaData(std::shared_ptr<ObjectActionListner>& l) : listener_(l) {}
  virtual ~WatchMetaData() {}
  std::shared_ptr<ObjectActionListner> listener_;
};

// base class for object watcher implementation strategy
// according to type of object e.g. file, directory, socket etc.
class ObjectWatcherImpl {
  public:

  virtual int addWatch(std::shared_ptr<Object> obj,
                           std::shared_ptr<ObjectActionListner> hndl,
                           unsigned int flags) = 0;

  virtual void removeWatch(int watchId) = 0;

//  virtual void removeWatch(std::shared_ptr<Object> obj);

  // sort of call back with action containing all info about
  // operation happened on obj
  virtual void handleActionOnObject(std::shared_ptr<Object>& obj,
                                    std::shared_ptr<WatchMetaData>& metadata,
                                    std::shared_ptr<WatchResult>& action) = 0;

  virtual ~ObjectWatcherImpl() {}

  virtual void refresh(uint64_t timeout = 10000000u) = 0;
};

}}


#endif /* WATCHERIMPL_HPP_ */
