#ifndef C_TIMER_H

#define C_TIMER_H

typedef timer_t int;

#define timer_init(t) \
    asm("getr %0,1" : "=r" (t));

#define timer_exit(t) \
    asm("freer res[%0]" :: "r" (t));

#define timer_in(t, i)                            \
    asm("in %0,res[%1]" : "=r" (i): "r" (t));

#define port_in_when_timerafter(t,i,v)              \
    asm("setd res[%0],%1" :: "r" (t), "r" (v)); \
    asm("setc res[%0],9" :: "r" (t));       \
    asm("in %0,res[%1]" : "=r" (i): "r" (t));

#endif
