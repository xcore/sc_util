#include <xs1.h>
#include "foo.h"
#include "mutual_thread_comm.h"

enum {
  FOO_CMDA,
  FOO_CMDB
} foo_cmd;


/*** Client Functions ***/

int foo_cmdA(chanend c)
{
  int x;
  mutual_comm_initiate(c);
  c <: FOO_CMDA;
  c :> x;
  mutual_comm_complete(c);
  return x;
}

void foo_cmdB(chanend c, int x)
{
  mutual_comm_initiate(c);
  c <: FOO_CMDB;
  c <: x;
  mutual_comm_complete(c);
}

#pragma select handler
void data_from_foo_server(chanend c, int &data)
{
  mutual_comm_notified(c);
  c :> data;
  mutual_comm_complete(c);
}

/*** Server ***/

#define PERIOD 50000

static void handle_cmd(chanend c, int cmd, int &x)
{
  switch (cmd) {
  case FOO_CMDA:
    c <: x;
    break;
  case FOO_CMDB:
    c :> x;
    break;
  }
}

void foo_server(chanend c) {
  timer tmr;
  int t;
  mutual_comm_state_t mstate;
  int is_response_to_notification;
  int data;
  int x = 0;

  mutual_comm_init_state(mstate);

  tmr :> t;
  while (1) {
    select
      {
      case tmr when timerafter(t) :> int tmp:
        // Something has happened in the server (in this case a timeout
        // put it could be a packet arriving on some pins/channel)
        // So we notify the client that we have some data
        data = t;
        t += PERIOD;
        mutual_comm_notify(c, mstate);
        break;
      case mutual_comm_transaction(c, is_response_to_notification, mstate):
        if (is_response_to_notification) {
          // The client has responded via the data_from_foo_server
          // function, we need to supply the data
          c <: data;
        }
        else {
          // The client has called one of the foo_cmd functions
          int cmd;
          c :> cmd;
          handle_cmd(c, cmd, x);
        }
        mutual_comm_complete_transaction(c,
                                         is_response_to_notification,
                                         mstate);
        break;
      }
  }
}

