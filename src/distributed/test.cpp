//
// test.cpp
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
//  Created on: Sep 21, 2013
//      Author: Manish Kumar
//
#include <iostream>

#include "hdfs.h"
#include <glog/logging.h>

int main(int argc, const char* argv[]) {
  google::InitGoogleLogging(argv[0]);

  struct hdfsBuilder* bld = hdfsNewBuilder();
  if (!bld) return -1;

  hdfsBuilderSetNameNode(bld, "hdfs://localhost");
  hdfsBuilderSetNameNodePort(bld, 0);

  hdfsFS hdfs = hdfsBuilderConnect(bld);

//  hdfsFS hdfs = hdfsConnect("hdfs://localhost", 0);

  int n;
  hdfsFileInfo* finfo = hdfsListDirectory(hdfs, "hdfs://localhost/user/Hadoop/", &n);
  if (!finfo) std::cout << "Error ==" << std::endl;
  std::cout << "dirs = " << n << std::endl;

//  hdfsFS hdfs = hdfsConnect("hdfs://localhost", 50070);

//  hdfsCopy(hdfs, "/tmp/test.cpp", hdfs, "/user/Hadoop/out/");

  hdfsDisconnect(hdfs);

  return 0;
}


