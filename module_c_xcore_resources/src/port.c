#include "port.h"

extern port port_init(int port_id);
extern port port_init_buffered(int port_id, int shift_width);
extern void port_exit(port p);
extern void output_data(port p, int data);
extern int  input_data(port p);
extern port port_when_pinseq(port p, int value);
extern port port_when_pinsneq(port p, int value);
extern port port_when_at_time(port p, int value);
extern void clear_port_condition(port p);
extern void clear_port_time_condition(port p);
