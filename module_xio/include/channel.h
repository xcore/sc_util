#ifndef C_CHAN_H
#define C_CHAN_H

#include <xccompat.h>

/** Type that denotes a stremaing channel-end. Streaming communication
 * channels comprise two connected streaming channel-ends and can be
 * created using s_chan_init(). Streaming channels should be deinitialised
 * using s_chan_free().
 */
typedef chanend streaming_chanend;

#include <channel_internal.h>


#if  !defined(__XC__) || defined(__DOXYGEN__)
/** Create a channel between a pair of
 * channel-ends. The channel-end variables must reside on the same core.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
inline void chan_alloc(chanend *c1, chanend *c2) {
  chanend c;
  asm("getr %0,2" : "=r" (c));
  *c1 = c;
  asm("getr %0,2" : "=r" (c));
  *c2 = c;
  asm("setd res[%0], %1" :: "r" (*c1), "r" (*c2));
  asm("setd res[%0], %1" :: "r" (*c2), "r" (*c1));
}

/** Create a streaming channel between a pair of streaming
 * channel-ends. The channel-end variables must reside on the same core.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
inline void s_chan_alloc(streaming_chanend *c1, streaming_chanend *c2) {
    chan_alloc(c1, c2);
}

/** Disconnect and deallocate a channel between a pair of
 * channel-ends.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
inline void chan_free(chanend c1, chanend c2) {
    asm volatile("freer res[%0]" :: "r" (c1));           \
    asm volatile("freer res[%0]" :: "r" (c2));
}


/** Disconnect and deallocate a streaming channel between a
 * pair of streaming channel-ends.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
inline void s_chan_free(streaming_chanend c1, streaming_chanend c2)
{
  s_chan_output_ctEND(c1);
  s_chan_output_ctEND(c2);
  s_chan_check_ctEND(c1);
  s_chan_check_ctEND(c1);
  asm volatile("freer res[%0]" :: "r" (c1));
  asm volatile("freer res[%0]" :: "r" (c2));
}
#endif


/** Output a control token onto a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param ct   control token to be output. Legal control tokens that can be
 *             used are 0 or any value in the range 3..191 inclusive.
 */
inline void s_chan_output_ct(streaming_chanend c, int ct) {
  asm volatile("outct res[%0],%1" :: "r" (c), "r" (ct));
}


/** Check that a specific control token is available on a
 * streaming channel-end. This function blocks until a token is available on
 * the streaming channel. If the available token is a control token and
 * has the value ``ct``, then the token is input and discarded. Otherwise
 * an exception is raised.
 *
 * \param c    the streaming channel-end.
 *
 * \param ct   control token that is expected on the streaming channel.
 */
inline void s_chan_check_ct(streaming_chanend c, int ct) {
    asm volatile("chkct res[%0],%1" :: "r" (c), "r" (ct));
}


/** Output a word over a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param data the word to be output.
 */
inline void s_chan_output_word(streaming_chanend c, int data) {
  asm volatile("out res[%0],%1" :: "r" (c), "r" (data));
}

/** Output an byte over a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param data the byte to be output.
 */
inline void s_chan_output_byte(streaming_chanend c, char data) {
  asm volatile("outt res[%0],%1" :: "r" (c), "r" (data));
}


/** Output a block of data over a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param buf  a pointer to the buffer containing the data to send
 *
 * \param n    the number of bytes to send
 */
inline void s_chan_output_block(streaming_chanend c, char buf[], int n) {
  // Note we could do this more efficiently depending on the size of n
  // and the alignment of buf
  for (int i=0;i<n;i++)
    s_chan_output_byte(c, buf[i]);
}


/** Input a word from a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \returns    the inputted integer.
 */
inline int s_chan_input_word(streaming_chanend c)
{
  int data;
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (c));
  return data;
}

/** Input a byte from a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \returns    the inputted byte
 */
inline char s_chan_input_byte(streaming_chanend c)
{
  char data;
  asm volatile("int %0,res[%1]" : "=r" (data): "r" (c));
  return data;
}

/** Input a block of data from a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param buf  a pointer to the memory region to fill
 *
 * \param n    the number of bytes to receive
 */
inline void s_chan_input_block(streaming_chanend c, char buf[], int n) {
  // Note we could do this more efficiently depending on the size of n
  // and the alignment of buf
  for (int i=0;i<n;i++)
    buf[i] = s_chan_input_byte(c);
}


/** Output a word over a channel-end.
 *
 * \param c    the channel-end.
 *
 * \param data the word to be output.
 */
inline void chan_output_word(chanend c, int data)
{
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  s_chan_output_word(c, data);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
}

/** Output a byte over a channel-end.
 *
 * \param c    the channel-end.
 *
 * \param data the byte to be output.
 */
inline void chan_output_byte(chanend c, char data)
{
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  s_chan_output_byte(c, data);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
}

/** Output a block of data over a channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param buf  a pointer to the buffer containing the data to send
 *
 * \param n    the number of bytes to send
 */
inline void chan_output_block(chanend c, char buf[], int n)
{
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  s_chan_output_block(c, buf, n);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
}


/** Input a word from a channel.
 *
 * \param c    the channel-end.
 *
 * \returns    the inputted word.
 */
inline int chan_input_word(chanend c) {
  int data;
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  data = s_chan_input_word(c);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  return data;
}

/** Input a byte from a channel.
 *
 * \param c    the channel-end.
 *
 * \returns    the inputted byte
 */
inline int chan_input_byte(chanend c) {
  int data;
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  data = s_chan_input_word(c);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  return data;
}


/** Input a block of data from a channel-end.
 *
 * \param c    the channel-end.
 *
 * \param buf  a pointer to the memory region to fill
 *
 * \param n    the number of bytes to receive
 */
inline void chan_input_block(chanend c, char buf[], int n)
{
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
  s_chan_input_block(c, buf, n);
  s_chan_output_ctEND(c);
  s_chan_check_ctEND(c);
}

#include "channel_transaction.h"

#endif
