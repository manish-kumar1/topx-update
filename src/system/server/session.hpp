//
// session.hpp
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
//  Created on: Aug 24, 2013
//      Author: Manish Kumar
//

#ifndef SESSION_H_
#define SESSION_H_

#include <protobuf/message.h>
#include <protobuf/descriptor.h>
#include <protobuf/service.h>

#include <boost/move/move.hpp>

#include <memory>

namespace system { namespace net {

class RpcController : public google::protobuf::RpcController {

  // Client-side methods ---------------------------------------------
  // These calls may be made from the client side only.  Their results
  // are undefined on the server side (may crash).

  // Resets the RpcController to its initial state so that it may be reused in
  // a new call.  Must not be called while an RPC is in progress.
  virtual void Reset() {
    errMsg_.clear();
    isFailed_ = false;
    isCancelling_ = false;
    isCancelled_ = false;
  }

  // After a call has finished, returns true if the call failed.  The possible
  // reasons for failure depend on the RPC implementation.  Failed() must not
  // be called before a call has finished.  If Failed() returns true, the
  // contents of the response message are undefined.
  virtual bool Failed() const {
    return isFailed_;
  }

  // If Failed() is true, returns a human-readable description of the error.
  virtual std::string ErrorText() const {
    return errMsg_;
  }

  // Advises the RPC system that the caller desires that the RPC call be
  // canceled.  The RPC system may cancel it immediately, may wait awhile and
  // then cancel it, or may not even cancel the call at all.  If the call is
  // canceled, the "done" callback will still be called and the RpcController
  // will indicate that the call failed at that time.
  virtual void StartCancel() {
    isCancelling_ = true;
  }

  // Server-side methods ---------------------------------------------
  // These calls may be made from the server side only.  Their results
  // are undefined on the client side (may crash).

  // Causes Failed() to return true on the client side.  "reason" will be
  // incorporated into the message returned by ErrorText().  If you find
  // you need to return machine-readable information about failures, you
  // should incorporate it into your response protocol buffer and should
  // NOT call SetFailed().
  virtual void SetFailed(const std::string& reason) {
    errMsg_ = reason;
  }

  // If true, indicates that the client canceled the RPC, so the server may
  // as well give up on replying to it.  The server should still call the
  // final "done" callback.
  virtual bool IsCanceled() {
    return isCancelled_;
  }

  // Asks that the given callback be called when the RPC is canceled.  The
  // callback will always be called exactly once.  If the RPC completes without
  // being canceled, the callback will be called after completion.  If the RPC
  // has already been canceled when NotifyOnCancel() is called, the callback
  // will be called immediately.
  //
  // NotifyOnCancel() must be called no more than once per request.
  virtual void NotifyOnCancel(google::protobuf::Closure* callback) {
    // TODO:
    return;
  }

  private:

  std::string errMsg_;
  bool        isFailed_;
  bool        isCancelling_;
  bool        isCancelled_;

};

// one connection per service channel

class ServiceConnectionChannel
      : public std::enable_shared_from_this<ServiceConnectionChannel>
      , public RpcController
      , public google::protobuf::RpcChannel {

  public:

  ServiceConnectionChannel(const std::string& name);

  virtual bool isAlive() const;
  virtual void close();

  virtual std::string getName() const;

  virtual ~ServiceConnectionChannel();

  int   registerProtoService(const std::shared_ptr<google::protobuf::Service> service);

  // Call the given method of the remote service.  The signature of this
  // procedure looks the same as Service::CallMethod(), but the requirements
  // are less strict in one important way:  the request and response objects
  // need not be of any specific class as long as their descriptors are
  // method->input_type() and method->output_type().
  virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                          RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf::Closure* done) = 0;

  private:
  BOOST_MOVABLE_BUT_NOT_COPYABLE(ServiceConnectionChannel);

  std::string   name_;
  size_t        id_;

  std::unordered_map<uint64_t, std::function<void, >
};


class Session {

};

}}



#endif /* SESSION_HPP_ */
