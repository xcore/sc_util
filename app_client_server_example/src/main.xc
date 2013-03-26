#include "platform.h"
#include <print.h>
#include "foo.h"

#define PERIOD 30000

void application(chanend c) {
  timer tmr;
  int t;
  int data;

  tmr :> t;
  while (1) {
    select
      {
      case tmr when timerafter(t) :> int tmp:
        // This task can call foo commands when it wants
        t += PERIOD;
        printstr("Calling foo_cmdA:");
        printintln(foo_cmdA(c));
        printstrln("Calling foo_cmdB.");
        foo_cmdB(c, t);
        break;

      // This case will fire when the server notifies us that some
      // data is available
      case data_from_foo_server(c, data):
        {
          printstr("Got some data from foo:");
          printintln(data);
          // It is possible to call commands here as well
          foo_cmdB(c, 20);
        }
        break;
      }
  }
}

int main() {
  chan c;
  par {
    application(c);
    foo_server(c);
  }
  return 0;
}
