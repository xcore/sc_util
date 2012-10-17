#ifndef __channel_transaction_h__
#define __channel_transaction_h__
#include <xs1.h>
typedef int transaction_inout_state;

/** Type that denotes a transacting channel-end. A transaction temporarily
 *  opens a route to the other side of the channel. During the transaction,
 *  you can use transaction channel operations for increased efficiency.
 *
 *  You can create a transacting chanend from a normal chanend using
 *  chan_init_transaction_master() and chan_init_transaction_slave().
 */
typedef struct transacting_chanend_s {
  chanend c;
  transaction_inout_state st;
} transacting_chanend;

#ifdef __XC__
#define __tc_get_reference_member(x,m) x.m
#else
#define __tc_get_reference_member(x,m) x->m
#endif

/** Start a transaction (master).
 *
 *  This initiates a *transaction* on a channel. A transaction temporarily
 *  opens a route to the other side of the channel. During the transaction,
 *  you can use transaction channel operations for increased efficiency.
 *
 *  This called must be matched by a call to chan_init_transaction_slave()
 *  on the other end of the channel.
 *
 *  A transaction should be closed with chan_complete_transaction()
 *
 * \param c   the chanend to initialize the transaction on
 * \returns   a version of the chanend to use within the transaction
 */
inline transacting_chanend chan_init_transaction_master(chanend c) {
  transacting_chanend tc;
  tc.c = c;
  tc.st = 0;
  s_chan_output_ct((streaming_chanend) c, XS1_CT_END);
  s_chan_check_ct((streaming_chanend) c, XS1_CT_END);
  return tc;
}

/** Start a transaction (slave).
 *
 *  This initiates a *transaction* on a channel. A transaction temporarily
 *  opens a route to the other side of the channel. During the transaction,
 *  you can use transaction channel operations for increased efficiency.
 *
 *  This called must be matched by a call to chan_init_transaction_master()
 *  on the other end of the channel.
 *
 *  A transaction should be closed with chan_complete_transaction()
 *
 * \param c   the chanend to initialize the transaction on
 * \returns   a version of the chanend to use within the transaction
 */
inline transacting_chanend chan_init_transaction_slave(chanend c)
{
  transacting_chanend tc;
  tc.c = c;
  tc.st = 1;
  s_chan_check_ct((streaming_chanend) c, XS1_CT_END);
  s_chan_output_ct((streaming_chanend) c, XS1_CT_END);
  return tc;
}


/** Complete a transaction.
 *
 * This function completes a transaction.
 * After this call the route between
 * the two ends of the channel is freed allowing other channel i/o to
 * use the communication network.
 *
 * This call should be accompanied by a call to
 * chan_complete_transaction on the other side of the
 * channel.
 *
 * \param c   the chanend to close the transaction on
 * \returns   a non-transacting version of the chanend
 */
inline chanend chan_complete_transaction(transacting_chanend c) {
  if (c.st) {
    s_chan_output_ct((streaming_chanend) c.c, XS1_CT_END);
    s_chan_check_ct((streaming_chanend) c.c, XS1_CT_END);
  }
  else {
    s_chan_check_ct((streaming_chanend) c.c, XS1_CT_END);
    s_chan_output_ct((streaming_chanend) c.c, XS1_CT_END);
  }
  return c.c;
}

#define __t_chan_change_to_input(c) \
  do { if (__tc_get_reference_member(c,st)) {__tc_get_reference_member(c,st) = 0;s_chan_check_ct(__tc_get_reference_member(c,c), XS1_CT_END);} } while (0)

#define __t_chan_change_to_output(c) \
  do { if (!__tc_get_reference_member(c,st)) {__tc_get_reference_member(c,st) = 1;s_chan_output_ct(__tc_get_reference_member(c,c), XS1_CT_END);} } while (0)


/** Check that a specific control token is available on a
 * transacting channel-end. This function blocks until a token is available on
 * the transacting channel. If the available token is a control token and
 * has the value ``ct``, then the token is input and discarded. Otherwise
 * an exception is raised.
 *
 * \param c    the transacting channel-end.
 *
 * \param ct   control token that is expected on the transacting channel.
 */
inline void t_chan_check_ct(REFERENCE_PARAM(transacting_chanend, c), int ct) {
  __t_chan_change_to_input(c);
  asm volatile("chkct res[%0],%1" :: "r" (__tc_get_reference_member(c,c)), "r" (ct));
}


/** Output a word over a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \param data the word to be output.
 */
inline void t_chan_output_word(REFERENCE_PARAM(transacting_chanend, c), int data) {
  __t_chan_change_to_output(c);
  asm volatile("out res[%0],%1" :: "r" (__tc_get_reference_member(c,c)), "r" (data));
}

/** Output an byte over a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \param data the byte to be output.
 */
inline void t_chan_output_byte(REFERENCE_PARAM(transacting_chanend, c), char data) {
  __t_chan_change_to_output(c);
  asm volatile("outt res[%0],%1" :: "r" (__tc_get_reference_member(c,c)), "r" (data));
}


/** Output a block of data over a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \param buf  a pointer to the buffer containing the data to send
 *
 * \param n    the number of bytes to send
 */
inline void t_chan_output_block(REFERENCE_PARAM(transacting_chanend, c), char buf[], int n) {
  // Note we could do this more efficiently depending on the size of n
  // and the alignment of buf
  __t_chan_change_to_output(c);
  for (int i=0;i<n;i++)
    s_chan_output_byte(__tc_get_reference_member(c,c), buf[i]);
}


/** Input a word from a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \returns    the inputted integer.
 */
inline int t_chan_input_word(REFERENCE_PARAM(transacting_chanend, c))
{
  int data;
  __t_chan_change_to_input(c);
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (__tc_get_reference_member(c,c)));
  return data;
}

/** Input a byte from a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \returns    the inputted byte
 */
inline char t_chan_input_byte(REFERENCE_PARAM(transacting_chanend, c))
{
  char data;
  __t_chan_change_to_input(c);
  asm volatile("int %0,res[%1]" : "=r" (data): "r" (__tc_get_reference_member(c,c)));
  return data;
}

/** Input a block of data from a transacting channel-end.
 *
 * \param c    the transacting channel-end.
 *
 * \param buf  a pointer to the memory region to fill
 *
 * \param n    the number of bytes to receive
 */
inline void t_chan_input_block(REFERENCE_PARAM(transacting_chanend, c), char buf[], int n) {
  // Note we could do this more efficiently depending on the size of n
  // and the alignment of buf
  __t_chan_change_to_input(c);
  for (int i=0;i<n;i++)
    buf[i] = s_chan_input_byte(__tc_get_reference_member(c,c));
}










#endif// __channel_transaction_h__

