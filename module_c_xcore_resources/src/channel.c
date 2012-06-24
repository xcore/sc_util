#include <xccompat.h>
#include <channel.h>

extern void s_send_ctEND(streaming_chanend c);
extern void s_check_ctEND(streaming_chanend c);

extern void chan_init(chanend *c1, chanend *c2);
extern void s_chan_init(streaming_chanend *c1, streaming_chanend *c2);
extern void chan_exit(chanend c1, chanend c2);
extern void s_chan_exit(streaming_chanend c1, streaming_chanend c2);
extern void s_send_ct(streaming_chanend c, int ct);
extern void s_check_ct(streaming_chanend c, int ct);
extern void s_send_word(streaming_chanend c, int data);
extern void s_send_byte(streaming_chanend c, char data);
extern void s_send_block(streaming_chanend c, char *buf, int n);
extern int  s_receive_word(streaming_chanend c);
extern char s_receive_byte(streaming_chanend c);
extern void s_receive_block(streaming_chanend c, char *buf, int n);
extern void send_word(chanend c, int data);
extern void send_byte(chanend c, char data);
extern void send_block(chanend c, char *buf, int n);
extern int  receive_word(chanend c);
extern int  receive_byte(chanend c);
extern void receive_block(chanend c, char *buf, int n);
