#include "mutual_thread_comm.h"
#include <xs1.h>


// ReactiveMaster Thread Functions

void mutual_comm_notified(chanend c)
{
  (void) inct(c);
  outuchar(c, 1);
  outct(c, XS1_CT_END);
  chkct(c, XS1_CT_END);
}

void mutual_comm_initiate(chanend c)
{
  outuchar(c, 0);
  outct(c, XS1_CT_END);
  chkct(c, XS1_CT_END);
  chkct(c, XS1_CT_END);
}

void mutual_comm_complete(chanend c)
{
  outct(c, XS1_CT_END);
  chkct(c, XS1_CT_END);
}

// NotifyingSlave Thread Functions

void mutual_comm_init_state(mutual_comm_state_t &notified)
{
  notified = 0;
}

void mutual_comm_transaction(chanend c,
                       int &is_response_to_notification,
                       mutual_comm_state_t &notified)
{
  is_response_to_notification = inuchar(c);
  (void) inct(c);

  if (is_response_to_notification) {
    notified = 0;
  } else {
    if (!notified)
      outct(c,XS1_CT_END);
  }
  outct(c,XS1_CT_END);
}

void mutual_comm_complete_transaction(chanend c,
                                      int &is_response_to_notification,
                                      mutual_comm_state_t &notified)
{
  chkct(c, XS1_CT_END);
  outct(c, XS1_CT_END);
  if (!is_response_to_notification && notified)
    outct(c, XS1_CT_END);
}


void mutual_comm_notify(chanend c, mutual_comm_state_t &notified)
{
  if (notified)
    return;

  outct(c, XS1_CT_END);
  notified = 1;
}


