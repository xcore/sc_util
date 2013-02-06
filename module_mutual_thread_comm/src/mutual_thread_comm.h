#ifndef _mutual_comm_h_
#define _mutual_comm_h_
#include <xccompat.h>

/* The communication pattern in this library is between two thread: the
 * NotifyingSlave and the ReactiveMaster.
 *
 * The NotifyingSlave can respond to a transaction initiated by the other size
 * but can also send a notification that it wants a transaction to occur.
 * The ReactiveMaster can initiate a transaction but can also select on a
 * notification occuring.
 *
 * This method allows a form of mutual bi-direction communication over
 * a single channel. See app_mutual_comm_example for a simple example of
 * its use.
 */

/***********************************************************************/
/* ReactiveMaster functions                                            */
/***********************************************************************/

/* Initiates a transaction with the NotifyingSlave */
void mutual_comm_initiate(chanend c);

/* Completes a transaction with the NotifyingSlave */
void mutual_comm_complete(chanend c);


#ifdef __XC__
#pragma select handler

void mutual_comm_notified(chanend c);

#endif // __XC__

/************************************************************************/
/* NotifyingSlave functions                                             */
/************************************************************************/


typedef int mutual_comm_state_t;

void mutual_comm_init_state(REFERENCE_PARAM(mutual_comm_state_t, state));

void mutual_comm_notify(chanend c, REFERENCE_PARAM(mutual_comm_state_t, state));

#ifdef __XC__

#pragma select handler
void mutual_comm_transaction(chanend c,
                int &is_data_request,
                mutual_comm_state_t &state);

void mutual_comm_complete_transaction(chanend c,
                                int &is_response_to_notification,
                                mutual_comm_state_t &state);

#endif








#endif // _mutual_comm_h_

