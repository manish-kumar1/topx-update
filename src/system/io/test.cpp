#include "Event.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

struct T {
  void operator()(int fd, short what) {
    char buf[64];
    int len;

    len = read(fd, buf, sizeof(buf));

    printf("Got an event on socket %d:%s%s%s%s [%s]\n",
        (int) fd,
        (what&EV_TIMEOUT) ? " timeout" : "",
        (what&EV_READ)    ? " read" : "",
        (what&EV_WRITE)   ? " write" : "",
        (what&EV_SIGNAL)  ? " signal" : "", buf);
  }
};

int main() {

  T handler;

  evutil_socket_t pair[2];
  const std::string msg = "Hello buddy!";

  if (::evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, pair) == -1) return -1;
  write(pair[0], msg.c_str(), 1+msg.size());
  shutdown(pair[0], SHUT_WR);

  myevent::Event<T> *e = new myevent::Event<T>(pair[1], EV_READ, handler);
  e->eventAdd(nullptr);
  e->dispatch();

//  ::event_add(e, nullptr);
//  ::event_base_dispatch(e->getEventBase());
  delete e;

  return 0;
}

