//
// watcher.hpp
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

#ifndef WATCHER_HPP_
#define WATCHER_HPP_

#include <memory>
#include <glog/logging.h>

#include "watcherImpl.hpp"
#include "../core/runnable.hpp"
#include "../core/object.hpp"

namespace mkTest { namespace system {

//using WatchID = int;

// will observe the OBJECT with strategy implemented with ObjectWatcherImpl
class ObjectWatcher : public ObjectActionListner, public std::enable_shared_from_this<ObjectWatcher> {

  public:
  ObjectWatcher(std::shared_ptr<Object> obj, unsigned int flags)
    : obj_(obj)
    , flags_ (flags)
  {
    wd_ = -1;
    LOG(INFO) << "called";
  }

  virtual void start() {
    auto listner = std::static_pointer_cast<ObjectActionListner>(shared_from_this());
    wd_ = pimpl_->addWatch(obj_, listner, flags_);
  }

  virtual void stop() {
    pimpl_->removeWatch(wd_);
    wd_ = -1;
  }

  virtual void cancel() {
    stop();
  }

  virtual void update() {
    pimpl_->refresh();
  }

  virtual void setImpl(std::shared_ptr<ObjectWatcherImpl> impl) {
    pimpl_ = impl;
  }

//  virtual void handleWatchResult(std::shared_ptr<Object> obj, std::shared_ptr<WatchResult> result) = 0;

  virtual ~ObjectWatcher() {
    LOG(INFO) << "~ObjectWatcher()";
  }

  protected:

  private:
  std::shared_ptr<ObjectWatcherImpl>    pimpl_;
  std::shared_ptr<Object>               obj_;
  unsigned int                          flags_;
  int                                   wd_;
};

}}

#endif /* WATCHER_HPP_ */
