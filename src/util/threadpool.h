//
// threadpool.h
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
//  Created on: Sep 7, 2013
//      Author: Manish Kumar
//

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

namespace util {

class ThreadPool {

  private:
  virtual ~ThreadPool();
};

class BoostThreadPool : private ThreadPool, public boost::threadpool::thread_pool {

};


#endif /* THREADPOOL_H_ */
