//
// Socket.h
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

#ifndef SOCKETDEVICE_H_
#define SOCKETDEVICE_H_

#include "device.h"

class SocketDevice : public Device {

  SocketDevice(const SocketDevice& rhs);

  fd_type open(int domain, int type, int protocol);

  ssize_t send(const std::string& buf, int flags = 0);
  ssize_t recv(void* buf, size_t len, int flags = 0);

  int setBlocking(int t = 0);
  int setNonBlocking();

  virtual ~SocketDevice();

  private:

};


#endif /* SOCKETDEVICE_H_ */
