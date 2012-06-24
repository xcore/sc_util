#ifndef C_PORT_H

#define C_PORT_H
#include <xccompat.h>

/** Initialise a port variable to a specific port. The port
 * should be one of XS1_PORT_1A .. XS1_PORT_32A as specified on the
 * datasheet and in the xs1.h include file. Either this function or
 * port_init_buffered() should be called once for each variable of type
 * ``port``; port_exit() should be called afterwards.
 *
 * \param port_id   value that identifies which port to drive.
 * \returns         port variable representing the initialise port
 */
inline port port_init(int port_id)
{
  port p = port_id;
  asm volatile("setc res[%0],8" :: "r" (p));
  return p;
}

/** Initialise a port variable to a specific port, and enables
 * the port to buffer and serialise/deserialise data. The port should be
 * one of XS1_PORT_1A .. XS1_PORT_32A as specified on the datasheet and in
 * the xs1.h include file. Either this function or port_init() should
 * be called once for each variable of type ``port``; port_exit()
 * should be called afterwards.
 *
 * \param p      port variable to initialise
 * \param port_id   value that identifies which port to drive.
 * \param shift_width  number of bits to serialise; must be 1, 2, 4, 8, or 32
 */
inline port port_init_buffered(int port_id, int shift_width)
{
  port p = port_id;
  asm volatile("setc res[%0],8" :: "r" (p));        \
  asm volatile("setc res[%0],0x200f" :: "r" (p));                       \
  asm volatile("settw res[%0],%1" :: "r" (p), "r" (shift_width));
  return p;
}

/** Uninitialise a port variable. This function switches off
 * the port.
 *
 * \param p      port variable to initialise
 */
inline void port_exit(port p)
{
  asm volatile("setc res[%0],0" :: "r" (p));
  return;
}


/** Outputs a value onto a port. In the case of an unbuffered
 * port, the value will be driven on the pins on the next clock cycle. In
 * the case of a buffered port, the data will be stored in the buffer, and
 * be serialised onto the output pins.
 *
 * \param p      port variable that inidicates which port to output to
 * \param data   value to output
 */
inline void output_data(port p, int data)
{
  asm volatile("out res[%0],%1" :: "r" (p), "r" (data));
}

/** Input a value from a port. In the case of an unbuffered
 * port, the data will be whatever is on the input pins. In the case of a
 * buffered port, this function will wait until the buffer is filled up with
 * deserialised data.
 *
 * \param p      port variable that inidicates which port to input from
 * \returns      the inputted data
 */
inline int input_data(port p)
{
  int data;
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Set a port to input or event when its pins match a specific value. This
 *  is usually used in conjunciton with input_data() e.g.
 *
 *  \code
 *
 *     x = input_data(port_when_pinseq(p,1))
 *
 *  \endcode
 *
 *  In the case of an unbuffered port, the data inputted
 *  be identical to the value. In the case of a buffered port, an input
 *  will wait until the value appears on the pins and then return that
 *  value and some previous values that have been deserialised.
 */
inline port port_when_pinseq(port p, int value)
{
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x11" :: "r" (p));
  return p;
}

/** Set a port to input or event when its pins do not
 *  match a specific value. This
 *  is usually used in conjunciton with input_data() e.g.
 *
 *  \code
 *
 *     x = input_data(port_when_pinsneq(p,1))
 *
 *  \endcode
 *
 * In the case of an unbuffered port, the inputted data
 * will be the non-matching pin values. In the case of a buffered port,
 * this macro will wait until a non matching value appears on the pins, and
 * then return that value and previous values that have been deserialised.
 */
inline port port_when_pinsneq(port p, int value)
{
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x19" :: "r" (p));
  return p;
}

#endif
