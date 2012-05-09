#include "platform.h"
#include "mutual_thread_comm.h"
#include <print.h>

#define THREADA_PERIOD 50000
#define THREADB_PERIOD 30000

void threadA(chanend c) {
  timer tmr;1
  int t;
  mutual_comm_state_t mstate;
  int is_response_to_notification;
  int val = 0;
  mutual_comm_init_state(mstate);

  tmr :> t;
  while (1) {
    select
      {
      case tmr when timerafter(t) :> int tmp:
        t += THREADA_PERIOD;
        //printstrln("Thread A: Notifying Thread B");
        mutual_comm_notify(c, mstate);
        break;
      case mutual_comm_transaction(c, is_response_to_notification, mstate):
        if (is_response_to_notification) {
          //printstrln("Thread A: Sending to Thread B");
          c <: val;
          val += 11;
        }
        else {
          int x;
          c :> x;
          printstr("Thread A: Received from Thread B: ");
          printintln(x);
        }
        mutual_comm_complete_transaction(c,
                                         is_response_to_notification,
                                         mstate);
        break;
      }
  }
}


void threadB(chanend c) {
  timer tmr;
  int t;
  int val = 0;

  tmr :> t;
  while (1) {
    select
      {
      case tmr when timerafter(t) :> int tmp:
        t += THREADB_PERIOD;
        //printstrln("Thread B: Sending to Thread A");
        mutual_comm_initiate(c);
        c <: val;
        val += 13;
        break;
      case mutual_comm_notified(c):
        {
          int x;
          //printstr("Thread B: Receiving from Thread A: ");
          c :> x;
          printstr("Thread B: Received from Thread A: ");
          printintln(x);
        }
        break;
      }
  }
}

int main() {
  chan c;
  par {
    threadA(c);
    threadB(c);
  }
  return 0;
}
