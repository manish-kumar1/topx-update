//
// filedevice.h
// 	Copyright 2013, 2014 Manish Kumar
//	manish.iitgcse@gmail.com
//
//	This file is part of Distributed TopX framework.
//
//	Distributed TopX is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	Distributed TopX is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with Distributed TopX.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Aug 18, 2013
//      Author: Manish Kumar
//

#ifndef FILEDEVICE_H_
#define FILEDEVICE_H_

#include "device.h"

class FileDevice : public Device {

  public:
  fd_type open(const std::string& path, int flags, mode_t mode = 0);
  int64_t size() const;

  void lock();
  void unlock();

  int flush() {
    return ::fsync(fd_);
  }

  void* mmap(size_t len, int prot, int flags, off_t offset = 0, void* addr = nullptr) {
    ismapped = true;
    return memoryMap(len, prot, flags, offset, addr);
  }
  private:

  bool ismapped = false;

};


#endif /* FILEDEVICE_H_ */
