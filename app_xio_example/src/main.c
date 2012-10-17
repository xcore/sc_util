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
