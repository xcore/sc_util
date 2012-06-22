#include <xs1.h>
#include <print.h>
#include <stddef.h>
#include "timer.h"
#include "port.h"
#include "channel.h"
#include "thread.h"

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

//:thread_group chan
chanend_t c1, c2, c3, c4;
//:thread_group end chan

//:thread funcs
void *f1(void *args) {
    chan_out_int(c1, 123);
    return NULL;
}

void *f2(void *args) {
    chan_out_int(c3, 1234);
    return NULL;
}
//:thread end funcs

//:thread main
void thread_test() {
    thread_t t2;
    unsigned int s1[100], s2[100];
    int i;

    chan_init(c1, c2);
    chan_init(c3, c4);

    thread_create_detached(&f1, s1, 100, NULL);
    thread_create(&t2, &f2, s2, 100, NULL);
    chan_in_int(c2, i);
    chan_in_int(c4, i);
    thread_join(t2);
    chan_exit(c1, c2);
    chan_exit(c3, c4);
}
//:thread end main

//:thread_group main
void *f3(void *args) {
    printstr("World\n");
    return NULL;
}

void *f4(void *args) {
    printstr("Hello\n");
    return NULL;
}

void thread_group_test() {
    thread_group_t tgroup;
    thread_group_create(&tgroup);

    unsigned int s1[100], s2[100];

    thread_create_in_group(&f3, tgroup, s1, 100, NULL);
    thread_create_in_group(&f4, tgroup, s2, 100, NULL);
    thread_group_start(tgroup);
    printstr("!!\n");
    thread_group_join(tgroup);
}
//:thread_group end main

int main(void) {
    porttest();
    timertest();
    thread_test();
    thread_group_test();
    return 0;
}
