//
// hdfs.cpp
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

#include "hdfs.h"

#include "hdfs.hpp"
#include "hdfsbuilder.hpp"

#include "system/exception/exception.hpp"

namespace mkTest { namespace distributed {

HdfsHndl::HdfsHndl(const HdfsConfiguration& conf) {
  fs_ = ::hdfsBuilderConnect(conf.getInternalBuilder());
  if (fs_ == nullptr) THROW("Couldn't create handle to HDFS");
}

#if 0
HdfsHndl::HdfsHndl(const std::string& nn, int port) {
  builder_ = new HDFSBuilder(nn, port);
  fs_ = ::hdfsBuilderConnect(builder_->getBuilder());
  if (fs_ == nullptr)
    THROW("Couldn't create handle to HDFS");
}

HdfsHndl::HdfsHndl(HDFSBuilder* builder) {
  if (this->builder_->isValid()) {
    delete builder_;
  }
  this->builder_ = builder;
  fs_ = ::hdfsBuilderConnect(builder_->getBuilder());
}
#endif

HdfsHndl::~HdfsHndl() {
  if (::hdfsDisconnect(fs_) != 0) THROW("hdfsDisconnect failed");
}

std::shared_ptr<HdfsFile> HdfsHndl::openFile (
    const std::string& path
    , int flags
    , int bufferSize
    , short replication
    , tSize blockSize)
{
  hdfsFile f = ::hdfsOpenFile(fs_, path.c_str(), flags, bufferSize, replication, blockSize);
  if (f == nullptr) THROW("Failed to open file " + path);
  return std::shared_ptr<HdfsFile>(new HdfsFile(f));
}

void HdfsHndl::closeFile(std::shared_ptr<HdfsFile>& file) {
  int ret = ::hdfsCloseFile(fs_, file->getInternalFile());
  if (ret != 0) THROW("Closing file");
}

std::vector<HdfsHndl::HdfsFileInfo> ls(const std::string& path) {
  int n = 0;
  ::hdfsFileInfo* finfo = ::hdfsListDirectory(fs_, path.c_str(), &n);
  std::shared_ptr<hdfsFile_internal> fileInfoInternal(new hdfsFile_internal(finfo, n));

  std::vector<HdfsHndl::HdfsFileInfo> v(n);
  for (int i = 0; i < n; ++i) v[i] = HdfsHndl::HdfsFileInfo(fileInfoInternal, i);

  return v;
}



}}
