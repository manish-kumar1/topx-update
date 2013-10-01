//
// configuration.hpp
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

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <unordered_map>
#include <string>
#include <forward_list>

namespace mkTest { namespace util {

class Configuration {

  public:
  Configuration();  // should be followed by load()
  Configuration(const std::string& name);
  Configuration(const Configuration& rhs);

  void load(const std::string& path);

  Configuration& operator = (const Configuration& rhs);

  std::string get(const std::string& key);
  int set(const std::string& key, const std::string& resource);

  private:

  class Resource : public std::enable_shared_from_this<Resource> {

    private:
    mkTest::Object  resources_;
    std::string     name_;
  };

  std::string   name_;
  std::forward_list<Resource> resourceList_;
  std::unordered_map<std::string, std::unique_ptr<Resource>> resourceMap_;

  static std::unordered_map<std::string, std::shared_ptr<Configuration>> registry_;
};

}}
#endif /* CONFIGURATION_HPP_ */
