//
// server.hpp
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
//  Created on: Aug 23, 2013
//      Author: Manish Kumar
//

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include "util/threadpool.h"

#include <utility>
#include <memory>
#include <string>
#include <unordered_map>

namespace system { namespace net {

// A server class, that runs on defined port
// can serve multiple services
// thread pool available

class Server : private boost::noncopyable<Server>, public std::enable_shared_from_this<Server> {

  public:
  explicit Server (boost::asio::io_service& io_service, int port);
  Server(const std::string& host, int port, int numThreads = 1);

  virtual ~Server();

  // start the server
  void start();

  // register services to handle requests
  int registerService(const std::shared_ptr<google::protobuf::Service> service);


  // disallow compiler defaults
  Server()         = delete;
  Server(Server&)  = delete;
  Server(Server&&) = delete;
  Server& operator = (const Server&) = delete;

  protected:

  void do_accept();

  void shutdown();

  private:

  void closeConnection(Connection* conn);

  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ip::tcp::socket   socket_;
  boost::asio::signal_set        signals_;
  std::mutex                     mutex_;

  // seesion name => session pointer
  std::unordered_map<std::string, std::shared_ptr<system::net::Session>> sessionTable;

  // offered service name => serviceChannel
  std::unordered_map<std::string, std::shared_ptr<system::net::ServiceConnectionChannel>>  serviceTable;

  // to service request across session
  //boost::threadpool::thread_pool pool_;
  std::unique_ptr<util::ThreadPool>   pool_;
};

}}


#endif /* SERVER_HPP_ */
