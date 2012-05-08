#ifndef C_CHAN_H

#define C_CHAN_H

/** Type that denotes a channel-end. Communication channels comprise
 * two connected channel-ends and can be created using chan_init().
 * Channels should be deinitialised using chan_exit().
 */
typedef unsigned int chanend_t;

/** Type that denotes a stremaing channel-end. Streaming communication
 * channels comprise two connected streaming channel-ends and can be
 * created using schan_init(). Streaming channels should be deinitialised
 * using schan_exit().
 */
typedef unsigned int streaming_chanend_t;

/** Macro that creates a streaming channel between a pair of streaming
 * channel-ends. The channel-end variables must reside on the same core.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
void schan_init(streaming_chanend_t c1, streaming_chanend_t c2);
#define schan_init(c1, c2) \
    chan_init(c1, c2);

/** Macro that creates a channel between a pair of
 * channel-ends. The channel-end variables must reside on the same core.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
void chan_init(chanend_t c1, chanend_t c2);
#define chan_init(c1, c2) \
    asm("getr %0,2" : "=r" (c1)); \
    asm("getr %0,2" : "=r" (c2)); \
    asm("setd res[%0], %1" :: "r" (c1), "r" (c2));  \
    asm("setd res[%0], %1" :: "r" (c2), "r" (c1)); 


/** Macro that disconnects and deallocates a channel between a pair of
 * channel-ends.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
void chan_exit(chanend_t c1, chanend_t c2);
#define chan_exit(c1, c2) \
    asm volatile("freer res[%0]" :: "r" (c1));           \
    asm volatile("freer res[%0]" :: "r" (c2)); 


/** Macro that disconnects and deallocates a streaming channel between a
 * pair of streaming channel-ends.
 *
 * \param c1   channel-end of one side
 * \param c2   channel-end of the other side
 */
void schan_exit(streaming_chanend_t c1, streaming_chanend_t c2);
#define schan_exit(c1, c2) \
    schan_outctEND(c1); \
    schan_outctEND(c2); \
    schan_chkctEND(c1); \
    schan_chkctEND(c2); \
    asm volatile("freer res[%0]" :: "r" (c1));           \
    asm volatile("freer res[%0]" :: "r" (c2)); 

// Internal use only.
#define schan_outctEND(c) \
    asm volatile("outct res[%0],1" :: "r" (c));

// Internal use only.
#define schan_chkctEND(c) \
    asm volatile("chkct res[%0],1" :: "r" (c));

/** Macro that outputs a control token onto a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param ct   control token to be output. Legal control tokens that can be
 *             used are 0 or any value in the range 3..191 inclusive.
 */
void schan_outct(streaming_chanend_t c, int ct);
#define schan_outct(c,i) \
    asm volatile("outct res[%0],%1" :: "r" (c), "r" (i));

/** Macro that checks that a specific control token is available on a
 * streaming channel-end. This macro blocks until a token is available on
 * th e streaming channel. If the available token is a control token and
 * has the value ``ct``, then the token is input and discarded. Otherwise
 * an exception is raised.
 *
 * \param c    the streaming channel-end.
 *
 * \param ct   control token that is expected on the streaming channel. If a different token arrives.
 */
void schan_chkct(streaming_chanend_t c, int ct);
#define schan_chkct(c,i) \
    asm volatile("chkct res[%0],%1" :: "r" (c), "r" (i));


/** Macro that outputs an integer over a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param data the integer to be output.
 */
void schan_out_int(streaming_chanend_t c, int data);
#define schan_out_int(c,data) \
    asm volatile("out res[%0],%1" :: "r" (c), "r" (data));

/** Macro that inputs an integer from a streaming channel-end.
 *
 * \param c    the streaming channel-end.
 *
 * \param data variable in which to write the inputted integer.
 */
void schan_in_int(streaming_chanend_t c, int data);
#define schan_in_int(c,data) \
    asm volatile("in %0,res[%1]" : "=r" (data): "r" (c));

/** Macro that outputs an integer over a channel-end.
 *
 * \param c    the channel-end.
 *
 * \param data the integer to be output.
 */
void chan_out_int(chanend_t c, int data);
#define chan_out_int(c,data) \
    schan_outctEND(c); \
    schan_chkctEND(c); \
    schan_out_int(c, data); \
    schan_outctEND(c); \
    schan_chkctEND(c);

/** Macro that inputs an integer from a channel.
 *
 * \param c    the channel-end.
 *
 * \param data variable in which to write the inputted integer.
 */
void chan_in_int(chanend_t c, int data);
#define chan_in_int(c,data) \
    schan_outctEND(c); \
    schan_chkctEND(c); \
    schan_in_int(c, data); \
    schan_chkctEND(c); \
    schan_outctEND(c);
    
#endif
