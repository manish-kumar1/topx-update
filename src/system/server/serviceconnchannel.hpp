//
// serviceconnchannel.hpp
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

#ifndef SERVICECONNCHANNEL_HPP_
#define SERVICECONNCHANNEL_HPP_

#include <functional>
#include <memory>
#include <unordered_map>

#include "server/connection.hpp"

class ProtobufDecoder;
class ServiceConnectionChannel : public Connection {

  public:

  using HandlerFunctor = std::function<void (const ProtobufDecoder*, std::shared_ptr<Connection>)>;
  using HandlerTable = std::unordered_map<uint64_t, HandlerFunctor>;

  explicit ServiceConnectionChannel(const std::string&);

  virtual std::shared_ptr<Connection> Span(boost::asio::ip::tcp::socket* socket);
  bool Attach(Connection* service_connection, boost::asio::ip::tcp::socket* socket);

  int registerService(google::protobuf::Service* service);

  void CallMethod(const google::protobuf::MethodDescriptor *method,
                  google::protobuf::RpcController *controller,
                  const google::protobuf::Message *request,
                  google::protobuf::Message *response,
                  google::protobuf::Closure *done);
  private:

  HandlerTable  handlerTable_;
};

#endif /* SERVICECONNCHANNEL_HPP_ */
