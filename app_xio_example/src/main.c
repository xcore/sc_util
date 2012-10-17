#include <xs1.h>
#include <print.h>
#include "xio.h"
#include "athread.h"
#include "sthread.h"

//:port main
void porttest() {
    port x, y;
    x = port_enable(XS1_PORT_1A);
    y = port_enable_buffered(XS1_PORT_1B, 32);
    port_output(x, 1);
    port_output(x, 0);
    port_output(x, 1);
    port_output(x, 0);
    port_output(y, 0xAAAAAAAA);
    port_output(y, 0xAAAAAAAA);
    port_output(y, 0xAAAAAAAA);
    port_output(y, 0xAAAAAAAA);
    port_disable(x);
    port_disable(y);
}
//:port end

//:timer main
void timertest() {
    timer tmr;
    int v;
    tmr = timer_alloc();
    v = timer_get_time(tmr);  // input current time value
    v += 100;           // add 100 = 1us as ref clock is 100 MHz
    timer_wait_until(tmr, v);
    timer_free(tmr);
}
//:timer end

//:sthread chan
chanend c1, c2, c3, c4;
//:sthread end chan

//:athread funcs
void f1() {
    chan_output_word(c1, 123);
    athread_exit();
}

void f2() {
    chan_output_word(c3, 1234);
    athread_exit();
}
//:athread end funcs

//:athread main
void athread_test() {
    athread_t t1, t2;
    unsigned int s1[100], s2[100];
    int i;

    chan_alloc(&c1, &c2);
    chan_alloc(&c3, &c4);
    athread_init(t1, s1, 100, f1);
    athread_init(t2, s2, 100, f2);
    i = chan_input_word(c2);
    i = chan_input_word(c4);
    chan_free(c1, c2);
    chan_free(c3, c4);
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

void select_test() {
  select(1,2,3);
}

int main(void) {
    porttest();
    timertest();
    athread_test();
    sthread_test();
    return 0;
}
