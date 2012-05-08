#include <xs1.h>
#include <print.h>
#include "timer.h"
#include "port.h"
#include "channel.h"
#include "thread.h"

void porttest() {
    port_t x, y;
    port_init(x, XS1_PORT_1A);
    port_init_buffered(y, XS1_PORT_1B, 32);
    port_out(x, 0xAAAAAAAA);
    port_out(x, 0xAAAAAAAA);
    port_out(x, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_out(y, 0xAAAAAAAA);
    port_exit(x);
    port_exit(y);
}

void timertest() {
    timer_t x;
    int t;

    timer_init(x);
    timer_in(x, t);
    t += 100;
    timer_in_when_timerafter(x, t, t);
    timer_exit(x);
}

chanend_t c1, c2, c3, c4;

void f1() {
    chan_out_int(c1, 123);
    thread_exit();
}

void f2() {
    chan_out_int(c3, 1234);
    thread_exit();
}

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

int main(void) {
    porttest();
    timertest();
    thread_test();
    return 0;
}
