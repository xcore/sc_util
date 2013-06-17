#include "producer_consumer.h"
#include "simple_printf.h"

#include <xs1.h>
#include "platform.h"
#include "random.h"
#include "xassert.h"

#ifdef SIM
static int chanend_to_int(chanend c) {
    int id;
    asm("mov %0, %1" : "=r"(id) : "r"(c));
    return id;
}
#endif

static void delay(timer t, int time) {
    int x;
    t :> x;
    t when timerafter(x+time) :> void;
}

static void produce(random_generator_t rand, chanend c0, chanend c1, chanend c2, chanend c3) {
    int n = random_get_random_number(rand) % 5;
    for (int i = 0; i < n; i++) {
        outct(c0, XS1_CT_END);
        outct(c1, XS1_CT_END);
        outct(c2, XS1_CT_END);
        outct(c3, XS1_CT_END);
    }
}

// Read from the channels until they are empty
//  - prioritise a channel for a number of attempts but always read from the other
//    channels to ensure that all tokens are read
static unsigned int consume(random_generator_t rand, chanend c0, chanend c1, chanend c2, chanend c3) {
    unsigned int total = 0;
    while (1) {
        unsigned char val;
        int found = 0;
        int c = random_get_random_number(rand) % 4;
        int num_attempts = random_get_random_number(rand) % 10;

        for (int i = 0; i < num_attempts; i++) {
            switch (c) {

            case 0:
                #pragma ordered
                select {
                    case inct_byref(c0, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c1, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c2, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c3, val): assert(val == XS1_CT_END); found += 1; break;
                    default: break;
                }
                break;

            case 1:
                #pragma ordered
                select {
                    case inct_byref(c1, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c2, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c3, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c0, val): assert(val == XS1_CT_END); found += 1; break;
                    default: break;
                }
                break;

            case 2:
                #pragma ordered
                select {
                    case inct_byref(c2, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c3, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c0, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c1, val): assert(val == XS1_CT_END); found += 1; break;
                    default: break;
                }
                break;

            case 3:
                #pragma ordered
                select {
                    case inct_byref(c3, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c0, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c1, val): assert(val == XS1_CT_END); found += 1; break;
                    case inct_byref(c2, val): assert(val == XS1_CT_END); found += 1; break;
                    default: break;
                }
                break;
            }
        }

        total += found;
        
        // Keep going until all channels are empty
        if (num_attempts && !found)
            return total;
    }
    return 0;
}

void test_producer_consumer(chanend c0, chanend c1, chanend c2, chanend c3) {
    timer t;
    unsigned i = 0;
    unsigned total = 0;
#ifdef SIM
    random_generator_t rand = random_create_generator_from_seed(chanend_to_int(c0));
#else
    random_generator_t rand = random_create_generator_from_hw_seed();
#endif
    while (1)
    {
        produce(rand, c0, c1, c2, c3);

        // Do some "work"
        delay(t, random_get_random_number(rand) % 1000);

        total += consume(rand, c0, c1, c2, c3);

        if ((i++ & 0xff) == 0)
            simple_printf("Consumed %d\n", total);
    }
}

