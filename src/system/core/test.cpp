#if 0
#include <iostream>
#include <sstream>
#include <memory>
#include "runnable.hpp"

using namespace std;
class foo : public Runnable {

  int fib(int n) {
    if (n < 3) return 1;
    else return fib(n-1) + fib(n-2);
  }

  public:
  explicit foo(int n) : n_(n) {}
  int run() {
    cout << "in foo run() " << endl;
    int res = fib(n_);
    if (n_ <= 10)
      std::this_thread::sleep_for(std::chrono::seconds(15));
    cout << "done foo run(" << n_ << "), res = " << res << endl;
    return res;
  }
  ~foo() {
    cout << "foo::~foo() fib(" << n_ << ") = " << getResult() << std::endl;
  }

  private:
  int n_;
};

void test (int n)
{
  foo o(n);
  o.execute();
}

int main(int argc, char*argv[]) {
  stringstream oss;
  oss << argv[1];
  int n;
  oss >> n;
  shared_ptr<foo> obj(new foo(n));
  obj->execute();
  cout << "second time" << endl;
  obj->execute();
//  test(n);
//  foo obj2(n/4);
//  obj2.execute();
  cout << "done main" << endl;
  return 0;
}
#endif
