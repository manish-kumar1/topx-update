//
// file.hpp
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

#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>
#include <fstream>

#include <unistd.h>
#include <fcntl.h>

#include "object.hpp"

//#include "system/exception/exception.hpp"

namespace mkTest { namespace system {

class File : public Object {

  public:
  File (const char* name, int flags = O_RDWR|O_CLOEXEC, mode_t mode = 0644) {
    fd_ = ::open(name, flags, mode);
    if (fd_ < 0); //THROW_EX("couldn't open file ", name);
    path_ = std::string(name);
  }

  void close() {
    int ret = ::close(fd_);
    if (ret != 0) {
  //    THROW_EX("couldn't close file", path_);
    }
  }

  virtual ~File () {}

  std::string getPath() const {
    return path_;
  }

  bool operator == (const File& rhs) {
    return fd_ == rhs.fd_;
  }

  private:
  int fd_;
  std::string path_;
};

}}
#endif /* FILE_HPP_ */
