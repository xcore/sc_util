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

//:thread main
void *input_thread(void *);

void thread_test() {
    thread_t t;
    unsigned int s[100];
    chanend_t c1, c2;
    chan_init(c1, c2);

    thread_create(&t, &input_thread, s, 100, &c2);
    chan_out_int(c1, 123);
    thread_join(t);
    chan_exit(c1, c2);
}

void *input_thread(void *args) {
    int result;
    chanend_t c = *(chanend_t*)args;
    chan_in_int(c, result);
    return NULL;
}
//:thread end main

//:thread_detached main
void thread_detached_test() {
    unsigned int s[100];
    chanend_t c1, c2;
    chan_init(c1, c2);

    thread_create_detached(&input_thread, s, 100, &c2);
    chan_out_int(c1, 123);
    chan_exit(c1, c2);
}
//:thread_detached end main

//:thread_group main
void *world_thread(void *args);
void *hello_thread(void *args);

void thread_group_test() {
    thread_group_t tgroup;
    thread_group_create(&tgroup);

    unsigned int s1[100], s2[100];

    thread_create_in_group(&world_thread, tgroup, s1, 100, NULL);
    thread_create_in_group(&hello_thread, tgroup, s2, 100, NULL);
    thread_group_start(tgroup);
    thread_group_sync(tgroup);
    thread_group_sync(tgroup);
    printstr("!\n");
    thread_group_join(tgroup);
}

void *world_thread(void *args) {
    thread_sync();
    printstr("World");
    thread_sync();
    return NULL;
}

void *hello_thread(void *args) {
    printstr("Hello ");
    thread_sync();
    thread_sync();
    return NULL;
}
//:thread_group end main

int main(void) {
    porttest();
    timertest();
    thread_test();
    thread_detached_test();
    thread_group_test();
    return 0;
}
