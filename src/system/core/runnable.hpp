//
// runnable.hpp
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
//  Created on: Sep 8, 2013
//      Author: Manish Kumar
//

#ifndef RUNNABLE_HPP_
#define RUNNABLE_HPP_

#include <thread>
#include <future>
#include <iostream>
#include <functional>

struct RunnableBaseI {
  virtual void execute() = 0;
};

class RunnableBase : public RunnableBaseI {
  public:
  explicit RunnableBase(std::packaged_task<int()>&& f) {
  //  std::cout << __PRETTY_FUNCTION__ << std::endl;
    task_ = std::move(f);
  }

  virtual void execute () {
    future_ = task_.get_future();
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    task_();
    //result_ = future_.get();
  }

  virtual ~RunnableBase() {}

  protected:
  std::packaged_task<int ()>  task_;
  std::future<int>  future_;
//  int result_;
};


class Runnable : public RunnableBase {

  public:
  explicit Runnable() : RunnableBase (std::packaged_task<int ()>(std::bind(&Runnable::run, this))) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  virtual int run() = 0;

  int getResult() {
    // http://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async
    // get the result
    return future_.get();
  }

  virtual ~Runnable() {
  //  std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};


#endif /* RUNNABLE_HPP_ */
