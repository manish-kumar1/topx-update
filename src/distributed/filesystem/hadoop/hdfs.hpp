//
// hdfs.hpp
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
//  Created on: Sep 22, 2013
//      Author: Manish Kumar
//

#ifndef HDFS_HPP_
#define HDFS_HPP_

#include "hdfs.h"

#include <glog/logging.h>
#include "hdfsbuilder.hpp"
#include "system/exception/exception.hpp"

namespace mkTest { namespace distributed {

// singleton instance to manage one HDFS

class HdfsHndl {

  public:
  HdfsHndl(const HdfsConfiguration& conf);

  std::shared_ptr<HdfsFile> openFile (
      const std::string& path
      , int flags
      , int bufferSize = 0
      , short replication = 0
      , tSize blockSize = 0
      ) throw (mkTest::Exception);

  void closeFile(std::shared_ptr<HdfsFile>& file);

  int exist(const std::string& path);

  int copy(const std::string& src, const std::string& dest);
  int move(const std::string& src, const std::string& dest);
  int remove(const std::string& path, int recurse);
  int mkdir(const std::string& path);

  private:

  class hdfsFileInfo_internal : private std::enable_shared_from_this<hdfsFileInfo_internal> {
    public:
    hdfsFileInfo_internal(::hdfsFileInfo* finfo, int n) {
      fileInfo_ = finfo;
      numEntries_ = n;
    }

    ~hdfsFileInfo_internal() {
      if (fileInfo_) ::hdfsFreeFileInfo(fileInfo_, numEntries_);
    }

    ::hdfsFileInfo* operator [] (int idx) {
      return &fileInfo_[idx];
    }

    private:
    ::hdfsFileInfo* fileInfo_;
    int             numEntries_;

  };

  // contain basic information about hdfs file
  class HdfsFileInfo {
    public:

    std::ostream& operator << (std::ostream& out) {
      ::hdfsFileInfo* me = (*internalInfo_)[idx_];
      out << me->mPermissions << " " << me->mReplication << " " << me->mOwner << " "
          << me->mGroup << " " << me->mSize << "/" << me->mBlockSize << " " << me->mLastMod << "/"
          << me->mLastAccess << " " << me->mName;

      if (me->mKind) out << "/";    // to denote its directory

      return out;
    }

    HdfsFileInfo(std::shared_ptr<hdfsFileInfo_internal>& fileInfo, int n) {
      internalInfo_ = fileInfo;
      idx_ = n;
    }

    ~HdfsFileInfo() {
      LOG(DEBUG) << "~FileInfo()";
    }

    private:
    std::shared_ptr<hdfsFileInfo_internal>  internalInfo_;
    int                                     idx_;
  };

  public:
  std::vector<HdfsFileInfo> ls(const std::string& path);

  int setReplication(const std::string& path, int replication);

  ~HdfsHndl();

  protected:

// deprecated
//  HdfsHndl(const std::string& nn = "default", int port = 0);
//  HdfsHndl(HDFSBuilder* builder);

  private:
//  HDFSBuilder*   builder_;
  hdfsFS         fs_;   // hdfs internal handle

//  static std::shared_ptr<HadoopFS>  instance_;
};

}}
#endif /* HDFS_HPP_ */
