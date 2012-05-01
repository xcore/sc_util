#ifndef C_THREAD_H

#define C_THREAD_H

typedef thread_t int;

#define thread_init(t, stack, stackWords, pc)    \
    asm("getr %0,1" : "=r" (t)); \
    asm("tinit t[%0]:sp,%1" :: "r" (t), "r" (&stack[stackWords-1])); \
    asm("getr %0,1" : "=r" (t));
    asm("getr %0,1" : "=r" (t));

#define thread_exit(t) \
    asm("freer res[%0]" :: "r" (t));

#endif
