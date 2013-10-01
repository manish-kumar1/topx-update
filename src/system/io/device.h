//
// device.h
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

#ifndef DEVICE_H_
#define DEVICE_H_

#include <unistd.h>
#include <sys/mman.h>

typedef int fd_type;

class Device {

  protected:

  Device(fd_type fd = fd_type(-1)) {
    fd_ = fd;
    obseleted_ = 0;
  }

  Device(const Device& rhs) {
    close();
    fd_ = rhs.getFd();
    rhs.obseleted();
  }

  void obseleted() {
    fd_ = fd_type(-1);
    obseleted_ = 1;
  }

  public:

  ssize_t read(void *buf, size_t nbyte, off_t offset = 0) {
    if (obseleted_) return 0;

    if (offset > 0) {
      return ::pread(fd_, buf, nbyte, offset);
    }
    else {
      return ::read(fd_, buf, nbyte);
    }
  }

  ssize_t write(const void *buf, size_t nbyte, off_t offset = 0) {
    if (obseleted_) return 0;

    if (offset > 0) {
      return ::pwrite(fd_, buf, nbyte, offset);
    } else {
      return ::write(fd_, buf, nbyte);
    }
  }

  void* memoryMap(size_t len, int prot, int flags, off_t offset = 0, void* addr = nullptr) {
    return ::mmap(addr, len, prot, flags, fd_, offset);
  }

  int memoryUnmap(void* addr, size_t len) {
    return ::munmap(addr, len);
  }

  fd_type getFd() const {
    if (obseleted_) return fd_type(-1);
    else return fd_;
  }

  int close() {
    return ::close(fd_);
  }

  virtual ~Device() = 0;

  private:

  fd_type   fd_;
  int       obseleted_;
};


#endif /* DEVICE_H_ */
