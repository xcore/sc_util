#ifndef C_PORT_H

#define C_PORT_H

/** Type that denotes a port. Variables of this type should be initalised
 * using port_init() or port_init_buffered(), and deinitialised using
 * port_exit().
 */
typedef unsigned int port_t;

/** Macro that initialises a port variable to a specific port. The port
 * should be one of XS1_PORT_1A .. XS1_PORT_32A as specified on the
 * datasheet and in the xs1.h include file. Either this function or
 * port_init_buffered() should be called once for each variable of type
 * ``port_t``; port_exit() should be called afterwards.
 *
 * \param p      port variable to initialise
 * \param port   value that identifies which port to drive.
 */
void port_init(port_t p, int port);
#define port_init(p, port) \
    p = port; \
    asm volatile("setc res[%0],8" :: "r" (p));

/** Macro that initialises a port variable to a specific port, and enables
 * teh port to buffer and serialise/deserialise data. The port should be
 * one of XS1_PORT_1A .. XS1_PORT_32A as specified on the datasheet and in
 * the xs1.h include file. Either this function or port_init() should
 * be called once for each variable of type ``port_t``; port_exit()
 * should be called afterwards.
 *
 * \param p      port variable to initialise
 * \param port   value that identifies which port to drive.
 * \param shift_width  number of bits to serialise; must be 1, 2, 4, 8, or 32
 */
void port_init_buffered(port_t p, int port, int shift_width);
#define port_init_buffered(p, port, shift_width) \
    p = port; \
    asm volatile("setc res[%0],8" :: "r" (p)); \
    asm volatile("setc res[%0],0x200f" :: "r" (p)); \
    asm volatile("settw res[%0],%1" :: "r" (p), "r" (shift_width));

/** Macro that uninitialises a port variable. This function switches off
 * the port.
 *
 * \param p      port variable to initialise
 */
void port_exit(port_t p);
#define port_exit(p) \
    asm volatile("setc res[%0],0" :: "r" (p));


/** Macro that outputs a value onto a port. In the case of an unbuffered
 * port, the value will be driven on the pins on the next clock cycle. In
 * the case of a buffered port, the data will be stored in the buffer, and
 * be serialised onto the output pins.
 *
 * \param p      port variable that inidicates which port to output to
 * \param data   value to output
 */
void port_out(port_t p, int data);
#define port_out(p,i) \
    asm volatile("out res[%0],%1" :: "r" (p), "r" (i));

/** Macro that inputs a value from a port. In the case of an unbuffered
 * port, the data will be whatever is on the input pins. In the case of a
 * buffered port, this macro will wait until the buffer is filled up with
 * deserialised data.
 *
 * \param p      port variable that inidicates which port to input from
 * \param data   variable to input into
 */
void port_in(port_t p, int data);
#define port_in(p,i) \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (p));

/** Macro that inputs a value from a port conditionally; when the pins
 * match a specific value. In the case of an unbuffered port, the data will
 * be identical to the value. In the case of a buffered port, this macro
 * will wait until the value appears on the pins, and then return that
 * value and previous values deserialised into ``data``.
 *
 * \param p      port variable that inidicates which port to input from
 * \param data   variable to input into
 * \param value  conditional value
 */
void port_in_when_pinseq(port_t p, int data, int value);
#define port_in_when_pinseq(p,data,value)              \
    asm volatile("setc res[%0],0x11" :: "r" (p));       \
    asm volatile("setd res[%0],%1" :: "r" (p), "r" (value)); \
    asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));

/** Macro that inputs a value from a port conditionally; when the pins do
 * not match a specific value. In the case of an unbuffered port, the data
 * will be the non-matchine pin values. In the case of a buffered port,
 * this macro will wait until a non matching value appears on the pins, and
 * then return that value and previous values deserialised into ``data``.
 *
 * \param p      port variable that inidicates which port to input from
 * \param data   variable to input into
 * \param value  conditional value
 */
void port_in_when_pinsneq(port_t p, int data, int value);
#define port_in_when_pinsneq(p,data,value)              \
    asm volatile("setc res[%0],0x19" :: "r" (p));       \
    asm volatile("setd res[%0],%1" :: "r" (p), "r" (value)); \
    asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));

#endif
