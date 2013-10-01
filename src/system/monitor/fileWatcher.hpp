//
// fileWatcher.hpp
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
//  Created on: Sep 11, 2013
//      Author: Manish Kumar
//

#ifndef FILEWATCHER_HPP_
#define FILEWATCHER_HPP_

#include <glog/logging.h>

#include "watcher.hpp"
#include "fileWatcherImpl.hpp"

#include "../core/file.hpp"
#include "../core/runnable.hpp"

namespace mkTest { namespace system {

class foo : public Runnable {
  public:
  explicit foo (std::shared_ptr<Object> obj, std::shared_ptr<WatchResult> result) {
    file_ = std::dynamic_pointer_cast<File>(obj);
    result_ = std::dynamic_pointer_cast<FileWatchResult>(result);
  }

  int run() {
    LOG(INFO) << file_->getPath() << ", result = " << *result_;
    return 0;
  }

  private:
  std::shared_ptr<File> file_;
  std::shared_ptr<FileWatchResult> result_;
};

class FileWatcher : public ObjectWatcher {
  public:
  explicit FileWatcher(std::shared_ptr<File> obj, unsigned int flags) : ObjectWatcher(obj, flags) {}

  void handleWatchResult(std::shared_ptr<Object>& obj, std::shared_ptr<WatchResult>& result) {
//    std::packaged_task<int (std::shared_ptr<Object>, std::shared_ptr<WatchResult>)> task (&printThis);
    LOG(INFO) << "called";
    std::lock_guard<std::mutex> lock(mutex_);
    foo(obj, result).execute();
  }

  private:
//  void printThis(std::shared_ptr<Object> obj, std::shared_ptr<WatchResult> result) {
//    std::shared_ptr<File> f = std::dynamic_pointer_cast<File>(obj);
//    std::shared_ptr<FileWatchResult> r = std::dynamic_pointer_cast<FileWatchResult>(result);
//
//    LOG(INFO) << f->getPath() << ", result = " << r->event.name << ", " << r->event.wd;
//  }

  std::mutex mutex_;
};

}}

#endif /* FILEWATCHER_HPP_ */
