//
// hdfsbuilder.hpp
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

#ifndef HDFSBUILDER_HPP_
#define HDFSBUILDER_HPP_

#include <string>

#include "hdfs.h"
#include "system/exception/exception.hpp"

namespace mkTest { namespace distributed {

// wrapper around provided hdfsbuilder

class HDFSBuilder {

  public:

  HDFSBuilder (const std::string& nn = "default", tPort port = 0) {
    builder_ = ::hdfsNewBuilder();
    if (builder_ == nullptr) THROW("hdfsNewBuilder failed");
    setNameNode(nn);
    setNameNodePort(port);
  }

  void setForceNewInstance() {
    ::hdfsBuilderSetForceNewInstance(this->builder_);
  }

  struct hdfsBuilder* getBuilder() {
    return builder_;
  }

  bool isValid() {
    return builder_ != nullptr;
  }

  ~HDFSBuilder () {
    if (isValid())
      ::hdfsFreeBuilder(this->builder_);
  }


  // deleted member
  HDFSBuilder () = delete;
  HDFSBuilder (HDFSBuilder&) = delete;
  HDFSBuilder (HDFSBuilder&&) = delete;
  HDFSBuilder& operator = (HDFSBuilder&) = delete;
  HDFSBuilder& operator = (HDFSBuilder&&) = delete;

  protected:
  void setNameNode(const std::string& nn) {
    ::hdfsBuilderSetNameNode(this->builder_, nn.c_str());
  }

  void setNameNodePort(tPort port) {
    ::hdfsBuilderSetNameNodePort(this->builder_, port);
  }

  void setUserName(const std::string& userName) {

  }

  int setConfStr(const std::string& key, const std::string& val) {
    return ::hdfsBuilderConfSetStr (builder_, key.c_str(), val.c_str());
  }

  int getConfStr(const std::string& key, std::string& val) {
    return -1;
  }

  private:

  struct hdfsBuilder* builder_;
};

}}


#endif /* HDFSBUILDER_HPP_ */
