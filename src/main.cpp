//
// main.hpp
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
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Sep 11, 2013
//      Author: Manish Kumar
//



#include <iostream>
#include <sys/inotify.h>
#include <glog/logging.h>

#include "system/monitor/fileWatcher.hpp"
#include "system/core/file.hpp"

using namespace std;
using namespace mkTest;
using namespace mkTest::system;

int main(int argc, const char*argv[])
{
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Starting test";

  std::shared_ptr<File> file(new File("/home"));
  std::shared_ptr<FileWatcherImpl> fimpl(new FileWatcherImpl);

  //std::shared_ptr<FileWatcher> fw (new FileWatcher(file, IN_CREATE | IN_MODIFY | IN_DELETE));
  std::shared_ptr<FileWatcher> fw (new FileWatcher(file, IN_ALL_EVENTS));
  fw->setImpl(fimpl);

  int t = 15;
  fw->start();
  while (1) {
    fw->update();
  }

}
