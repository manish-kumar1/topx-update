//
// Event.h
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
//  Created on: Aug 17, 2013
//      Author: Manish Kumar
//

#ifndef MYEVENT_H_
#define MYEVENT_H_

#include <event2/event.h>
#include <event2/util.h>

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>

#include <stdarg.h>
#include <cerrno>
#include <fcntl.h>

namespace myevent {

struct libEventIfStruct //: public event
{
  struct event_base*   base_;

  int   fd_;
  int   prio_;
  int   flags_;
  short events_;
  void* args_;

  struct event* self_;
};


// interface to members/functions of libevent
class EventI : protected libEventIfStruct {

  public:

  EventI () = delete;
  EventI (EventI&) = delete;
  EventI (const EventI&) = delete;
  EventI (EventI&&) = delete;
  EventI& operator = (const EventI&) = delete;

  private:

  void EventII(struct event_config* ev_config) throw () {
    base_ = ev_config ? ::event_base_new_with_config(ev_config) : ::event_base_new();

    prio_ = 1;
    flags_ = 0x0;

    args_ = nullptr;
  }

  protected:

  EventI(int fd = -1, short events = 0, struct event_config* ev_config = nullptr)
  {
    fd_ = fd;
    events_ = events;

    EventII(ev_config);
  }

  public:

  static void event_callback(int fd, short events, void *arg) {
    EventI* pEventIf = reinterpret_cast<EventI*>(arg);

    pEventIf->_cb_handler(fd, events);
  }

  virtual void _cb_handler(int fd, short events) {
    //std::cerr << "in EventI _cb_handler" << std::endl;
  }

  bool pending(short ev) const throw () {
    return ::event_pending(self_, ev, nullptr);
  }

  timeval timeout() const {
    timeval tv;
    ::event_pending(self_, EV_TIMEOUT, &tv);
    return tv;
  }

  void setPriority(int prio) {
    if (::event_priority_set(self_, prio) == 0)
      prio_ = prio;
  }

  event_base* getEventBase() const {
    return base_;
  }

  virtual ~EventI() throw() {
    std::cerr << "in ~EventI" << std::endl;
    if (!base_) ::event_base_free(base_);
  }

};

// generic event type
template<typename H>
class Event : public EventI {
  public:

  explicit Event(int fd, short events, H& handler, struct event_config* config = nullptr) : EventI(fd, events, config) {
    this->handler_ = &handler;

    self_ = ::event_new(base_, fd_, events_, event_callback, reinterpret_cast<void*>(this));
  }

  virtual void _cb_handler(int fd, short events) {
    //std::cout << "In Event event_callback" << std::endl;
    (*handler_)(fd, events);
  }

  virtual int eventAdd(const struct timeval *tv = nullptr) {
    return ::event_add(self_, tv);
  }

  virtual int dispatch() {
    return ::event_base_dispatch(base_);
  }

  virtual ~Event() {
    std::cerr << "in ~Event" << std::endl;
    if (self_) {
      ::event_free(self_);
      self_ = nullptr;
    }
  }

  Event() = delete;
  Event(Event&&) = delete;
  Event(Event&) = delete;

  private:

  H*  handler_;
};

}
#endif /* MYEVENT_H_ */
