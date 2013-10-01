//
// fileWatcherImpl.hpp
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

#ifndef FILEWATCHERIMPL_HPP_
#define FILEWATCHERIMPL_HPP_

#include <memory>
#include <unordered_map>
#include <glog/logging.h>
#include <sys/inotify.h>
#include <cstring>
#include <algorithm>
#include <cstdio>

#include "../core/file.hpp"
#include "../monitor/watcherImpl.hpp"
#include "../exception/exception.hpp"

namespace mkTest { namespace system {

// impl article http://www.linuxjournal.com/article/8478

struct FileWatchMetaData : public WatchMetaData {
  explicit FileWatchMetaData(int wd, std::shared_ptr<File>& file, std::shared_ptr<ObjectActionListner>& listner)
    : WatchMetaData(listner), wd_(wd), file_(file) {}

  int wd_;
  std::shared_ptr<File> file_;
};

class FileWatchResult : public WatchResult {
  public:
  explicit FileWatchResult(struct inotify_event* pevent) {
    wd =     pevent->wd;
    cookie = pevent->cookie;
    mask   = pevent->mask;

    if (pevent->len) name = std::string(pevent->name);
    else name = std::string("NULL");
  }

  int wd;
  unsigned int cookie, mask;
  std::string name;
  friend std::ostream& operator << (std::ostream& oss, const FileWatchResult& r);
};

std::ostream& operator << (std::ostream& oss, const FileWatchResult& r) {
  oss << std::endl
      << "name   = " << r.name << std::endl
      << "mask   = " << r.mask << std::endl
      << "wd     = " << r.wd << std::endl
      << "cookie = " << r.cookie << std::endl;
  return oss;
}

class FileWatcherImpl : public ObjectWatcherImpl {
  public:
  explicit FileWatcherImpl() {
    inotifyFD_ = inotify_init();
    if (inotifyFD_ == -1) {
      THROW("inotify_init() failed");
    }
  }

  int addWatch(std::shared_ptr<Object> obj, std::shared_ptr<ObjectActionListner> hdlr, unsigned int flags) {
    std::shared_ptr<File> f = std::dynamic_pointer_cast<File>(obj);
 
    int wd = inotify_add_watch (inotifyFD_, f->getPath().c_str(), flags);
    if (wd < 0) {
      std::cout << "add_watch_failed for path" << f->getPath() << " with error " << std::endl;
      perror("inotify_add_watch");

      if (wd == -1) {
        THROW_EX("inotify_add_watch(), FileNotFound", f->getPath());
      }
      else {
        THROW_EX("inotify_add_watch(), Error", wd);
      }
    }

    std::shared_ptr<FileWatchMetaData> data(new FileWatchMetaData(wd, f, hdlr));
    fileWatchMetadata_[wd] = data;
    LOG(INFO) << "Added watch on " << f->getPath() << ", wd = " << wd;
    return wd;
  }

  void removeWatch (int watchId) {
    auto it = fileWatchMetadata_.find(watchId);
    if (it != fileWatchMetadata_.end()) {
      inotify_rm_watch(inotifyFD_, watchId);
      fileWatchMetadata_.erase(it);
    }
  }

//  void removeWatch (const std::shared_ptr<Object>& obj) {
//    std::shared_ptr<File> file = std::dynamic_pointer_cast<File>(obj);
//    auto newEnd = std::remove_if (
//        fileWatchMetadata_.begin()
//        ,fileWatchMetadata_.end()
//        ,[file](std::unordered_map<int, std::shared_ptr<FileWatchMetaData>>::value_type& p){ return p.second->file_ == file;}
//    );
//
//    fileWatchMetadata_.erase(newEnd, fileWatchMetadata_.end());
//  }

  void refresh(uint64_t timeout) {
    struct timeval tm;
    tm.tv_sec = timeout/1000000u;
    tm.tv_usec = timeout%1000000u;

    FD_ZERO(&fds_);
    FD_SET(inotifyFD_, &fds_);

    int ret = select (inotifyFD_ + 1, &fds_, NULL, NULL, &tm);
    if (ret < 0) {
      THROW_EX("select failed on inotify", ret);
    }
    else if (ret == 0) {
      LOG(INFO) << "timed out after " << tm.tv_sec << " for inotify select";
    }
    else if (FD_ISSET (inotifyFD_, &fds_)) {
      ssize_t len, i = 0;
      std::array<char, (1u << 12)> buff;

      len = read (inotifyFD_, buff.data(), buff.size());

      while (i < len)
      {
        struct inotify_event *pevent = (struct inotify_event *)&buff[i];

        std::shared_ptr<WatchResult> result(new FileWatchResult(pevent));
        std::shared_ptr<FileWatchMetaData> metadata = fileWatchMetadata_[pevent->wd];

        std::shared_ptr<Object> file = std::static_pointer_cast<Object>(metadata->file_);
        std::shared_ptr<WatchMetaData> meta = std::static_pointer_cast<WatchMetaData>(metadata);

        handleActionOnObject(file, meta, result);
        i += sizeof(struct inotify_event) + pevent->len;
      }
    }
  }

  void handleActionOnObject(std::shared_ptr<Object>& obj, std::shared_ptr<WatchMetaData>& metadata, std::shared_ptr<WatchResult>& action) {
    LOG(INFO) << " called for file " << std::dynamic_pointer_cast<File>(obj)->getPath();
    metadata->listener_->handleWatchResult(obj, action);
  }

  ~FileWatcherImpl() {
    try {
      fileWatchMetadata_.clear();
      ::close (inotifyFD_);
      LOG(INFO) << "closed inotifyFD_" << inotifyFD_;
    } catch (...) {
      LOG(WARNING) << "caught an exception";
    }
  }

  private:
  int            inotifyFD_;
  fd_set         fds_;
  std::unordered_map<int, std::shared_ptr<FileWatchMetaData>> fileWatchMetadata_;
};

}}
#endif /* FILEWATCHERIMPL_HPP_ */
