#include "timer.h"

void timertest() {
    timer_t x;
    int t;

    timer_init(x);
    timer_in(x, t);
    t += 100;
    timer_in_when_timerafter(x, t, t);
    timer_exit(x);
}


int main(void) {
    timertest();
    return 0;
}
