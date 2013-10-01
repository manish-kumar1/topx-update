//
// hdfsFile.hpp
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

#ifndef HDFSFILE_HPP_
#define HDFSFILE_HPP_

#include <ios>

#include "hdfs.h"

namespace mkTest { namespace distributed {
class HdfsFile {
  public:

  HdfsFile() = delete;
  HdfsFile(HdfsFile&) = delete;
  HdfsFile& operator = (const HdfsFile&) = delete;

  void close() throw (std::exception);

  int64_t seek(int64_t off);

  int64_t tell();

  int32_t read (void* buffer, int32_t len);

  int32_t write (const void* buffer, int32_t len);

  int   flush() throw (std::exception);

  HdfsFile& operator << (const std::string val);
//  HdfsFile& operator << (int val);
//  HdfsFile& operator << (unsigned int val);
//  HdfsFile& operator << (long long val);
//  HdfsFile& operator << (double val);

  HdfsFile& operator >> (std::string& str);

  void register_callback (std::ios_base::event_callback fn, int index);

  protected:
  // private constructor, hide from general access
  HdfsFile(::hdfsFile f);

  ::hdfsFile getInternalFile();


  int flushClinetBuffer();

  private:
//  const hdfsFS&    fs_;    // filesystem handle
//  std::string path_;
  ::hdfsFile _M_hdfsFile_;

  friend class HdfsHndl;

};

}}
#endif /* HDFSFILE_HPP_ */
