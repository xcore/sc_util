#include <xs1.h>
#include <print.h>
#include "timer.h"
#include "port.h"
#include "channel.h"
#include "athread.h"

//:port main
void porttest() {
    port_t x, y;
    port_init(x, XS1_PORT_1A);
    port_init_buffered(y, XS1_PORT_1B, 32);
    port_out(x, 1);
    port_out(x, 0);
    port_out(x, 1);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_exit(x);
    port_exit(y);
}
//:port end

//:timer main
void timertest() {
    timer_t tmr;
    int v;

    timer_init(tmr);
    timer_in(tmr, v);           // input current time value
    v += 100;      // add 100 = 1us as ref clock is 100 MHz
    timer_in_when_timerafter(tmr, v, v);  // wait for v+100
    timer_exit(tmr);
}
//:timer end

//:thread chan
chanend_t c1, c2, c3, c4;
//:thread end chan

//:thread funcs
void f1() {
    chan_out_int(c1, 123);
    thread_exit();
}

void f2() {
    chan_out_int(c3, 1234);
    thread_exit();
}
//:thread end funcs

//:thread main
void thread_test() {
    thread_t t1, t2;
    unsigned int s1[100], s2[100];
    int i;

    chan_init(c1, c2);
    chan_init(c3, c4);
    thread_init(t1, s1, 100, f1);
    thread_init(t2, s2, 100, f2);
    chan_in_int(c2, i);
    chan_in_int(c4, i);
    chan_exit(c1, c2);
    chan_exit(c3, c4);
}
//:thread end main

int main(void) {
    porttest();
    timertest();
    thread_test();
    return 0;
}
