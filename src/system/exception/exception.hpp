//
// exception.hpp
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
//  Created on: Sep 11, 2013
//      Author: Manish Kumar
//

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <ostream>
#include <sstream>

namespace mkTest {

template <class T>
class Exception;

template <>
class Exception<const char*>;


template <>
class Exception<const char*> : std::exception {
  public:
    explicit Exception (const char* const m,  // message
                        const char* file,     // file
                        const char* fun,      // function
                        int l) throw ():      // line number
                        msg_(m),
                        filename_(file),function_(fun),
                        line_(l) {}

    ~Exception()throw(){}

    const char* what()const throw(){
      std::ostringstream oss;
      oss << filename_ << " [" << function_ << ":" << line_ << "]: EXCEPTION " << msg_;
      return oss.str().c_str();
    }

  private:
    const char *  msg_;
    const char *  filename_;
    const char *  function_;
    int     line_;
};



template <typename T>
class Exception : public std::exception {
  public:
  explicit Exception (const char* const m,  // message
                      const T& o,           // any object
                      const char* file,     // file
                      const char* fun,      // function
                      int l) throw ():      // line number
                      msg_(m), obj_(o),
                      filename_(file),function_(fun),
                      line_(l) {}

  const char * what () const throw (){
    std::ostringstream oss;
    oss << filename_ << " [" << function_ << ":" << line_ << "]: EXCEPTION " << msg_ << " {" << obj_ << "}";
    return oss.str().c_str();
  }

//  Exception (const Exception<T>& rhs) throw () {
//    filename_ = rhs.filename_;
//    function_ = rhs.function_;
//    line_     = rhs.line_;
//    obj_      = rhs.obj_;
//
//    msg_      = nullptr;    // TODO:
//
//    //*this = rhs;
//  }
//
//  Exception operator = (const Exception<T>& rhs) {
//    filename_ = rhs.filename_;
//    function_ = rhs.function_;
//    line_     = rhs.line_;
//    obj_      = rhs.obj_;
//    msg_      = rhs.msg_;
//
//    return *this;
//  }

//  Exception (Exception&&) = delete;
//  Exception operator = (Exception&&) = delete;
//  Exception operator = (const Exception&&) = delete;

  ~Exception () throw() {}

  private:
  const char *  msg_;
  T             obj_;
  const char *  filename_;
  const char *  function_;
  int     line_;
};


template<typename T>
void throwException(const char* const m, const T& o, const char* fl, const char* fun, int l) {
  throw Exception<T>(m, o, fl, fun, l);
}

void throwException(const char* const m, const char* fl, const char* fun, int l) {
  throw Exception<const char*>(m, fl, fun, l);
}

#define THROW_EX(M, O)  {throwException(static_cast<const char*>(M), O, __FILE__, __PRETTY_FUNCTION__, __LINE__);}
#define THROW(M)  {throwException(static_cast<const char*>(M), __FILE__, __PRETTY_FUNCTION__, __LINE__);}
}


#endif /* EXCEPTION_HPP_ */
