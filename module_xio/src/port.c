#include "port.h"

extern inline port port_enable(int port_id);
extern inline port port_enable_buffered(int port_id, int shift_width);
extern inline void port_disable(port p);
extern inline void port_output(port p, int data);
extern inline void port_output_at_time(port p, int data, int t);
extern inline int port_output_shift_right(port p, int data);
extern inline int port_output_shift_right_at_time(port p, int data, int t);
extern inline int port_input(port p);
extern inline int port_input_when_pinseq(port p, int value);
extern inline int port_input_when_pinsneq(port p, int value);
extern inline int port_input_at_time(port p, int t);
extern inline int port_input_shift_right(port p);
extern inline int port_input_shift_right_when_pinseq(port p, int value);
extern inline int port_input_shift_right_when_pinsneq(port p, int value);
extern inline int port_input_shift_right_at_time(port p, int t);
extern inline int port_force_input(port p, REFERENCE_PARAM(int,n));
extern inline int port_get_timestamp(port p);
extern inline void port_set_condition(port p, port_condition_t c);
extern inline void port_set_conditional_data(port p, int d);
extern inline void port_set_time_condition(port p, int t);
extern inline void port_clear_condition(port p);
extern inline void port_clear_time_condition(port p);
extern inline void port_clear_buffer(port p);
extern inline unsigned port_endin(port p);




