//
// hdfsconfiguration.hpp
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
//  Created on: Sep 29, 2013
//      Author: Manish Kumar
//

#ifndef HDFSCONFIGURATION_HPP_
#define HDFSCONFIGURATION_HPP_

#include "system/exception/exception.hpp"
#include "util/configuration.hpp"
#include "hdfsbuilder.hpp"

namespace mkTest { namespace distributed {

// would contain a generic way of defining configuration related to hdfs
// At this moment hdfsbuilder defines that, where one can set several params

class HdfsConfiguration {
  public:
  HdfsConfiguration() {
    try {
      pConfig_ = new util::Configuration();
      pHdfsBuilder_ = new HDFSBuilder();
    } catch (std::exception& e) {
      THROW_EX("caught exception in constructor", e);
    }
  }

  HdfsConfiguration(const std::string& configFilePath) {
    try {
      pConfig_ = new util::Configuration(configFilePath);
      pHdfsBuilder_ = new HDFSBuilder(pConfig_);
    } catch (std::exception& e) {
      THROW_EX("caught exception in constructor", e);
    }
  }

  int set(const std::string& key, const std::string& val) {
    pConfig_->set(key, val);
    return pHdfsBuilder_->setConfStr(key, val);
  }

  struct hdfsBuilder* getInternalBuilder() const {
    return pHdfsBuilder_->getBuilder();
  }

  private:
  util::Configuration* pConfig_;
  // keep builder here & provide uniform configuration interface
  // through this class
  HDFSBuilder*         pHdfsBuilder_;
};

}}
#endif /* HDFSCONFIGURATION_HPP_ */
