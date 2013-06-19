#include "mutual_thread_comm.h"
#include "producer_consumer.h"

#include <xs1.h>
#include <print.h>
#include "platform.h"
#include "random.h"
#include "xassert.h"
#include "debug_print.h"

static inline void send_uchar(chanend c, unsigned char x) {
    c <: x;
}

static inline void send_master(chanend c, unsigned char x) {
    master {
        c <: x;
    }
}

static inline void send_slave(chanend c, unsigned char x) {
    slave {
        c <: x;
    }
}

static inline void send_check_master(chanend c, unsigned char x) {
    master {
        unsigned char expected = x + 1;
        c <: x;
        c :> x;
        assert(x == expected);
    }
}

static inline void send_check_slave(chanend c, unsigned char x) {
    slave {
        unsigned char expected = x + 1;
        c <: x;
        c :> x;
        assert(x == expected);
    }
}

static inline void check_uchar(chanend c, unsigned char expected) {
    unsigned char x;
    c :> x;
    assert(x == expected);
}

static inline void check_master(chanend c, unsigned char expected) {
    master {
        unsigned char x;
        c :> x;
        assert(x == expected);
    }
}

static inline void check_slave(chanend c, unsigned char expected) {
    slave {
        unsigned char x;
        c :> x;
        assert(x == expected);
    }
}

static inline void check_send_slave(chanend c, unsigned char expected) {
    slave {
        unsigned char x;
        c :> x;
        assert(x == expected);
        x += 1;
        c <: x;
    }
}

static inline void check_send_master(chanend c, unsigned char expected) {
    master {
        unsigned char x;
        c :> x;
        assert(x == expected);
        x += 1;
        c <: x;
    }
}

#define test_server_notify(c, f)                                                        \
    mutual_comm_notify(c, mstate);                                                      \
    select {                                                                            \
        case mutual_comm_transaction(c, is_response_to_notification, mstate):           \
            if (is_response_to_notification) {                                          \
                f;                                                                      \
            } else {                                                                    \
                unreachable("ERROR\n");                                                 \
            }                                                                           \
            mutual_comm_complete_transaction(c, is_response_to_notification, mstate);   \
            break;                                                                      \
    }

#define test_server_respond(c, f)                                                       \
    select {                                                                            \
        case mutual_comm_transaction(c, is_response_to_notification, mstate):           \
            if (is_response_to_notification) {                                          \
                unreachable("ERROR\n");                                                 \
            } else {                                                                    \
                f;                                                                      \
            }                                                                           \
            mutual_comm_complete_transaction(c, is_response_to_notification, mstate);   \
            break;                                                                      \
    }

void test_server(chanend c) {
    int iteration = 1;
    int is_response_to_notification = 0;
    mutual_comm_state_t mstate;
    mutual_comm_init_state(mstate);

    while (1) {
        unsigned char x = iteration;
        test_server_notify(c, check_uchar(c, x));
        test_server_notify(c, send_uchar(c, x));

        test_server_notify(c, check_master(c, x));
        test_server_notify(c, send_master(c, x));

        test_server_notify(c, check_slave(c, x));
        test_server_notify(c, send_slave(c, x));

        test_server_notify(c, check_send_master(c, x));
        test_server_notify(c, send_check_master(c, x));

        test_server_notify(c, check_send_slave(c, x));
        test_server_notify(c, send_check_slave(c, x));

        test_server_respond(c, check_uchar(c, x));
        test_server_respond(c, send_uchar(c, x));

        test_server_respond(c, check_master(c, x));
        test_server_respond(c, send_master(c, x));

        test_server_respond(c, check_slave(c, x));
        test_server_respond(c, send_slave(c, x));

        test_server_respond(c, check_send_master(c, x));
        test_server_respond(c, send_check_master(c, x));

        test_server_respond(c, check_send_slave(c, x));
        test_server_respond(c, send_check_slave(c, x));

        debug_printf("Test pass %d\n", iteration);
        iteration += 1;
    }
}

#define test_client_notified(c, f)      \
    select {                            \
        case mutual_comm_notified(c):   \
            f;                          \
            mutual_comm_complete(c);    \
            break;                      \
    }

#define test_client_initiate(c, f)      \
    mutual_comm_initiate(c);            \
    f;                                  \
    mutual_comm_complete(c);            \

void test_client(chanend c) {
    unsigned char x = 1;
    while (1)
    {
        test_client_notified(c, send_uchar(c, x));
        test_client_notified(c, check_uchar(c, x));

        test_client_notified(c, send_slave(c, x));
        test_client_notified(c, check_slave(c, x));

        test_client_notified(c, send_master(c, x));
        test_client_notified(c, check_master(c, x));

        test_client_notified(c, send_check_slave(c, x));
        test_client_notified(c, check_send_slave(c, x));

        test_client_notified(c, send_check_master(c, x));
        test_client_notified(c, check_send_master(c, x));

        test_client_initiate(c, send_uchar(c, x));
        test_client_initiate(c, check_uchar(c, x));

        test_client_initiate(c, send_slave(c, x));
        test_client_initiate(c, check_slave(c, x));

        test_client_initiate(c, send_master(c, x));
        test_client_initiate(c, check_master(c, x));

        test_client_initiate(c, send_check_slave(c, x));
        test_client_initiate(c, check_send_slave(c, x));

        test_client_initiate(c, send_check_master(c, x));
        test_client_initiate(c, check_send_master(c, x));

        x += 1;
    }
}

int main() {
  chan c;
  chan c0, c1, c2, c3;
  chan c4, c5, c6, c7;
  chan c8, c9, c10, c11;
  par {
    on tile[0] : test_producer_consumer(c0, c1, c2, c3);
    on tile[1] : test_producer_consumer(c0, c1, c2, c3);
    on tile[0] : test_producer_consumer(c4, c5, c6, c7);
    on tile[1] : test_producer_consumer(c4, c5, c6, c7);
    on tile[0] : test_producer_consumer(c8, c9, c10, c11);
    on tile[1] : test_producer_consumer(c8, c9, c10, c11);

    on tile[0] : test_client(c);
    on tile[1] : test_server(c);
  }
  return 0;
}
