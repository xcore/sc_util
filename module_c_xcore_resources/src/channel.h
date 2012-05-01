#ifndef C_CHAN_H

#define C_CHAN_H

typedef chanend_t int;
typedef streaming_chanend_t int;

#define schan_init(c1, c2) \
    chan_init(c1, c2);

#define chan_init(c1, c2) \
    asm("getr %0,2" : "=r" (c1)); \
    asm("getr %0,2" : "=r" (c2)); \
    asm("setd res[%0], %1" :: "r" (c1), "r" (c2));  \
    asm("setd res[%0], %1" :: "r" (c2), "r" (c1)); 

#define chan_exit(c1, c2) \
    asm("freer res[%0]" : "=r" (c1)); \
    asm("freer res[%0]" : "=r" (c2)); 

#define schan_exit(c1, c2) \
    schan_outctEND(c1); \
    schan_outctEND(c2); \
    schan_chkctEND(c1); \
    schan_chkctEND(c2); \
    asm("freer res[%0]" : "=r" (c1)); \
    asm("freer res[%0]" : "=r" (c2)); 

#define schan_outctEND(c) \
    asm("outct res[%0],1" :: "r" (c));

#define schan_outct(c,i) \
    asm("outct res[%0],%1" :: "r" (c), "r" (i));

#define schan_chkct(c,i) \
    asm("chkct res[%0],%1" :: "r" (c), "r" (i));

#define schan_out_int(c,i) \
    asm("out res[%0],%1" :: "r" (c), "r" (i));

#define schan_in_int(c,i) \
    asm("out %0,res[%1]" : "=r" (i): "r" (c));

#define chan_out_int(c,i) \
    schan_outctEND(c); \
    schan_chkctEND(c); \
    schan_out_int(c, i); \
    schan_outctEND(c);

#define chan_in_int(c,i) \
    schan_outctEND(c); \
    schan_chkctEND(c); \
    schan_in_int(c, i); \
    schan_chkctEND(c);
    
#endif
