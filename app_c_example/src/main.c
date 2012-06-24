#include <xs1.h>
#include <print.h>
#include "cxc.h"

//:port main
void porttest() {
    port x, y;
    x = port_init(XS1_PORT_1A);
    y = port_init_buffered(XS1_PORT_1B, 32);
    output_data(x, 1);
    output_data(x, 0);
    output_data(x, 1);
    output_data(x, 0);
    output_data(y, 0xAAAAAAAA);
    output_data(y, 0xAAAAAAAA);
    output_data(y, 0xAAAAAAAA);
    output_data(y, 0xAAAAAAAA);
    port_exit(x);
    port_exit(y);
}
//:port end

//:timer main
void timertest() {
    timer tmr;
    int v;
    tmr = timer_init();
    v = get_time(tmr);  // input current time value
    v += 100;           // add 100 = 1us as ref clock is 100 MHz
    wait_until(tmr, v);
    timer_exit(tmr);
}
//:timer end

//:sthread chan
chanend c1, c2, c3, c4;
//:sthread end chan

//:athread funcs
void f1() {
    send_word(c1, 123);
    athread_exit();
}

void f2() {
    send_word(c3, 1234);
    athread_exit();
}
//:athread end funcs

//:athread main
void athread_test() {
    athread_t t1, t2;
    unsigned int s1[100], s2[100];
    int i;

    chan_init(&c1, &c2);
    chan_init(&c3, &c4);
    athread_init(t1, s1, 100, f1);
    athread_init(t2, s2, 100, f2);
    i = receive_word(c2);
    i = receive_word(c4);
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
