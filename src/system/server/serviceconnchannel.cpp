//
// serviceconnchannel.cpp
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
//  Created on: Sep 6, 2013
//      Author: Manish Kumar
//

#include <glog/logging.h>

#include "serviceconnchannel.hpp"

ServiceConnectionChannel::ServiceConnectionChannel(const std::string& name)
                          : Connection(name) {
  LOG(INFO) << "ServiceConnection crate with name = " << name;
}

std::shared_ptr<Connection> ServiceConnectionChannel::Span(boost::asio::ip::tcp::socket* sock) {
  std::shared_ptr<ServiceConnectionChannel> conn(new ServiceConnectionChannel(name()+".span"));
  if (!conn->Attach(this, socket)) {
    conn->reset();
  }
  return conn;
}

bool ServiceConnectionChannel::Attach(Connection* service_connection, boost::asio::ip::tcp::socket* socket) {

}
