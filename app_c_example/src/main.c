#include <xs1.h>
#include "timer.h"
#include "port.h"

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


int main(void) {
    porttest();
    timertest();
    fork();
    return 0;
}
