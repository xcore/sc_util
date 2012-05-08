#include <xs1.h>
#include <print.h>
#include "timer.h"
#include "port.h"
#include "channel.h"
#include "athread.h"
#include "sthread.h"

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

//:sthread chan
chanend_t c1, c2, c3, c4;
//:sthread end chan

//:athread funcs
void f1() {
    chan_out_int(c1, 123);
    athread_exit();
}

void f2() {
    chan_out_int(c3, 1234);
    athread_exit();
}
//:athread end funcs

//:athread main
void athread_test() {
    athread_t t1, t2;
    unsigned int s1[100], s2[100];
    int i;

    chan_init(c1, c2);
    chan_init(c3, c4);
    athread_init(t1, s1, 100, f1);
    athread_init(t2, s2, 100, f2);
    chan_in_int(c2, i);
    chan_in_int(c4, i);
    chan_exit(c1, c2);
    chan_exit(c3, c4);
}
//:athread end main

//:sthread main
void f3() {
    printstr("World\n");
    sthread_exit();
}

void f4() {
    printstr("Hello\n");
    sthread_exit();
}

void sthread_test() {
    sthread_t t1, t2;
    sthread_sync_t s;
    unsigned int s1[100], s2[100];

    sthread_sync_init(s);
    sthread_init(t1, s, s1, 100, f3);
    sthread_init(t2, s, s2, 100, f4);
    sthread_start(s);
    printstr("!!\n");
    sthread_join(s);
}
//:sthread end main

int main(void) {
    porttest();
    timertest();
    athread_test();
    sthread_test();
    return 0;
}
