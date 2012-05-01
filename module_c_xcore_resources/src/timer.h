#ifndef C_TIMER_H

#define C_TIMER_H

typedef int timer_t;

#define timer_init(t) \
    asm volatile("getr %0,1" : "=r" (t));

#define timer_exit(t) \
    asm volatile("freer res[%0]" :: "r" (t));

#define timer_in(t, i)                            \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));

#define timer_in_when_timerafter(t,i,v)              \
    asm volatile("setd res[%0],%1" :: "r" (t), "r" (v)); \
    asm volatile("setc res[%0],9" :: "r" (t));       \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));

#endif
