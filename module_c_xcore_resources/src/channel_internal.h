#ifndef C_CHAN_INTERNAL_H
#define C_CHAN_INTERNAL_H

inline void s_send_ctEND(streaming_chanend c)
{
  asm("outct res[%0],1"::"r"(c));
}

inline void s_check_ctEND(streaming_chanend c)
{
  asm("chkct res[%0],1"::"r"(c));
}

#endif
