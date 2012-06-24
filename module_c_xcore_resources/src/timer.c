#include "timer.h"

extern timer timer_init(void);
extern void timer_exit(timer t);
extern int get_time(timer t);
extern timer timer_when_timerafter(timer tmr, int time);
extern void wait_until(timer tmr, int time);
extern void delay(int period);

