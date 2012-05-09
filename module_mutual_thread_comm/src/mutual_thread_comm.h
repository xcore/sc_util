#ifndef _mutual_comm_h_
#define _mutual_comm_h_
#include <xccompat.h>

typedef int mutual_comm_state_t;

void mutual_comm_init_state(REFERENCE_PARAM(mutual_comm_state_t, state));

#ifdef __XC__

#pragma select handler
void mutual_comm_transaction(chanend c,
                int &is_data_request,
                mutual_comm_state_t &state);

void mutual_comm_complete_transaction(chanend c,
                                int &is_response_to_notification,
                                mutual_comm_state_t &state);

#endif

void mutual_comm_notify(chanend c, REFERENCE_PARAM(mutual_comm_state_t, state));


void mutual_comm_initiate(chanend c);


#ifdef __XC__
#pragma select handler
void mutual_comm_notified(chanend c);

#endif






#endif // _mutual_comm_h_

