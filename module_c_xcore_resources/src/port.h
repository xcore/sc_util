#ifndef C_PORT_H

#define C_PORT_H

typedef int port_t;

#define port_init(p, port) \
    p = port; \
    asm volatile("setc res[%0],8" :: "r" (p));

#define port_init_buffered(p, port, shift_width) \
    p = port; \
    asm volatile("setc res[%0],8" :: "r" (p)); \
    asm volatile("setc res[%0],0x200f" :: "r" (p)); \
    asm volatile("settw res[%0],%1" :: "r" (p), "r" (shift_width));

#define port_exit(p) \
    asm volatile("setc res[%0],0" :: "r" (p));


#define port_out(p,i) \
    asm volatile("out res[%0],%1" :: "r" (p), "r" (i));

#define port_in(p,i) \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (p));

#define port_in_when_pinseq(p,i,v)              \
    asm volatile("setc res[%0],0x11" :: "r" (p));       \
    asm volatile("setd res[%0],%1" :: "r" (p), "r" (v)); \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (p));

#define port_in_when_pinsneq(p,i,v)              \
    asm volatile("setc res[%0],0x19" :: "r" (p));       \
    asm volatile("setd res[%0],%1" :: "r" (p), "r" (v)); \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (p));

#endif
