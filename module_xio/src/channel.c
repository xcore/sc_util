#include <xccompat.h>
#include <channel.h>

extern void s_chan_output_ctEND(streaming_chanend c);
extern void s_chan_check_ctEND(streaming_chanend c);

extern void chan_alloc(chanend *c1, chanend *c2);
extern void s_chan_alloc(streaming_chanend *c1, streaming_chanend *c2);
extern void chan_free(chanend c1, chanend c2);
extern void s_chan_free(streaming_chanend c1, streaming_chanend c2);
extern void s_chan_output_ct(streaming_chanend c, int ct);
extern void s_chan_check_ct(streaming_chanend c, int ct);
extern void s_chan_output_word(streaming_chanend c, int data);
extern void s_chan_output_byte(streaming_chanend c, char data);
extern void s_chan_output_block(streaming_chanend c, char buf[], int n);
extern int  s_chan_input_word(streaming_chanend c);
extern char s_chan_input_byte(streaming_chanend c);
extern void s_chan_input_block(streaming_chanend c, char buf[], int n);
extern void chan_output_word(chanend c, int data);
extern void chan_output_byte(chanend c, char data);
extern void chan_output_block(chanend c, char *buf, int n);
extern int  chan_input_word(chanend c);
extern int  chan_input_byte(chanend c);
extern void chan_input_block(chanend c, char *buf, int n);

extern inline transacting_chanend chan_init_transaction_master(chanend c);
extern inline transacting_chanend chan_init_transaction_slave(chanend c);
extern inline chanend chan_complete_transaction(transacting_chanend c);
extern inline void t_chan_check_ct(REFERENCE_PARAM(transacting_chanend, c), int ct);
extern inline void t_chan_output_word(REFERENCE_PARAM(transacting_chanend, c), int data);
extern inline void t_chan_output_byte(REFERENCE_PARAM(transacting_chanend, c), char data);
extern inline void t_chan_output_block(REFERENCE_PARAM(transacting_chanend, c), char buf[], int n);
extern inline int t_chan_input_word(REFERENCE_PARAM(transacting_chanend, c));
extern inline char t_chan_input_byte(REFERENCE_PARAM(transacting_chanend, c));
extern inline void t_chan_input_block(REFERENCE_PARAM(transacting_chanend, c), char buf[], int n);
