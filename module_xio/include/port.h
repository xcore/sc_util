#ifndef C_PORT_H

#define C_PORT_H
#include <xccompat.h>

/** Enables a port.
 *
 * The port
 * should be one of XS1_PORT_1A .. XS1_PORT_32A as specified on the
 * datasheet and in the xs1.h include file. Either this function or
 * port_init_buffered() should be called once for each variable of type
 * ``port``; port_free() should be called afterwards.
 *
 * \param port_id   value that identifies which port to drive.
 * \returns         port variable representing the initialised port
 */
inline port port_enable(int port_id)
{
  port p = port_id;
  asm volatile("setc res[%0],8" :: "r" (p));
  return p;
}

/** Initialise a port variable to a specific port, and enables
 * the port to buffer and serialise/deserialise data.
 *
 * The port should be
 * one of XS1_PORT_1A .. XS1_PORT_32A as specified on the datasheet and in
 * the xs1.h include file. Either this function or port_init() should
 * be called once for each variable of type ``port``; port_free()
 * should be called afterwards.
 *
 * \param port_id   value that identifies which port to drive.
 * \param shift_width  number of bits to serialise; must be 1, 2, 4, 8, or 32
 * \returns         port variable representing the initialised port
 */
inline port port_enable_buffered(int port_id, int shift_width)
{
  port p = port_id;
  asm volatile("setc res[%0],8" :: "r" (p));        \
  asm volatile("setc res[%0],0x200f" :: "r" (p));                       \
  asm volatile("settw res[%0],%1" :: "r" (p), "r" (shift_width));
  return p;
}

/** Uninitialise a port variable and disable the port.
 *  This function switches off
 *  the port.
 *
 * \param p      port variable to initialise
 */
inline void port_disable(port p)
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
inline void port_output(port p, int data)
{
  asm volatile("out res[%0],%1" :: "r" (p), "r" (data));
}

/** Outputs a value onto a port at a specified time.
 *
 * In the case of an unbuffered
 * port, the value will be driven on the pins when on the clock cycle that
 * moves the port counter to the specified time. In
 * the case of a buffered port, the data will be stored in the buffer, and
 * be serialised onto the output pins at the point that the time is reached.
 *
 * \param p      port variable that inidicates which port to output to
 * \param data   value to output
 * \param t      the time of the output
 */
inline void port_output_at_time(port p, int data, int t)
{
  asm volatile("setpt res[%0],%1"::"r"(p),"r"(t));
  asm volatile("out res[%0],%1" :: "r" (p), "r" (data));
}

/** Outputs a value onto a port and shifts the output data.
 * In the case of an unbuffered
 * port, the value will be driven on the pins on the next clock cycle. In
 * the case of a buffered port, the data will be stored in the buffer, and
 * be serialised onto the output pins.
 *
 * \param p      port variable that inidicates which port to output to
 * \param data   value to output
 *
 * \returns      the output data shifted right by the
 *               transfer width of the port.
 */
inline int port_output_shift_right(port p, int data)
{
  asm volatile("outshr res[%0],%1" :: "r" (p), "r" (data));
  return (data);
}

/** Outputs a value onto a port at a specified time and shifts the output data.
 *
 * In the case of an unbuffered
 * port, the value will be driven on the pins when on the clock cycle that
 * moves the port counter to the specified time. In
 * the case of a buffered port, the data will be stored in the buffer, and
 * be serialised onto the output pins at the point that the time is reached.
 *
 * \param p      port variable that inidicates which port to output to
 * \param data   value to output
 * \param t      the time of the output
 *
 * \returns      the output data shifted right by the transfer width
 *               of the port
 *
 */
inline int port_output_shift_right_at_time(port p, int data, int t)
{
  asm volatile("setpt res[%0],%1"::"r"(p),"r"(t));
  asm volatile("outshr res[%0],%1" :: "r" (p), "r" (data));
  return (data);
}


/** Input a value from a port. In the case of an unbuffered
 * port, the data will be whatever is on the input pins. In the case of a
 * buffered port, this function will wait until the buffer is filled up with
 * deserialised data.
 *
 * \param p      port variable that inidicates which port to input from
 * \returns      the inputted data
 */
inline int port_input(port p)
{
  int data;
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its pins match a specific value.
 *
 *  In the case of an unbuffered port, the data inputted
 *  be identical to the value. In the case of a buffered port, an input
 *  will wait until the value appears on the pins and then return that
 *  value and some previous values that have been deserialised.
 *
 * \param p      port variable that inidicates which port to input from
 * \param value  the value to match against the pins
 * \returns      the inputted data
 */
inline int port_input_when_pinseq(port p, int value)
{
  int data;
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x11" :: "r" (p));
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its pins do not
 *  match a specific value.
 *
 * In the case of an unbuffered port, the inputted data
 * will be the non-matching pin values. In the case of a buffered port,
 * this macro will wait until a non matching value appears on the pins, and
 * then return that value and previous values that have been deserialised.
 *
 * \param p      port variable that inidicates which port to input from
 * \param value  the value to match against the pins
 * \returns      the inputted data
 */
inline int port_input_when_pinsneq(port p, int value)
{
  int data;
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x19" :: "r" (p));
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its counter is at a specific time.
 *
 *  In the case of an unbuffered port, the data will be inputted when the
 *  counter reaches time ``t``. In the case of a buffered port, an input
 *  will wait until the given time and then will start capturing data,
 *  returning a value when the buffer is full.
 *
 * \param p      port variable that inidicates which port to input from
 * \param t      the time to do input
 * \returns      the inputted data
 */
inline int port_input_at_time(port p, int t)
{
  int data;
  asm volatile("setpt res[%0],%1" :: "r" (p), "r" (t));
  asm volatile("in %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}


/** Input a value from a port and shift the data.
 *
 * In the case of an unbuffered
 * port, the data will be whatever is on the input pins. In the case of a
 * buffered port, this function will wait until the buffer is filled up with
 * deserialised data.
 *
 * \param p      port variable that inidicates which port to input from
 *
 * \returns      the input data shifted right by the transfer width
 *               of the port
 */
inline int port_input_shift_right(port p)
{
  int data;
  asm volatile("inshr %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its pins match a specific value  and shift the data.
 *
 *  In the case of an unbuffered port, the data inputted
 *  be identical to the value. In the case of a buffered port, an input
 *  will wait until the value appears on the pins and then return that
 *  value and some previous values that have been deserialised.
 *
 * \param p      port variable that inidicates which port to input from
 * \param value  the value to match against the pins
 *
 * \returns      the input data shifted right by the transfer width
 *               of the port
 */
inline int port_input_shift_right_when_pinseq(port p, int value)
{
  int data;
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x11" :: "r" (p));
  asm volatile("inshr %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its pins do not
 *  match a specific value  and shift the data.
 *
 * In the case of an unbuffered port, the inputted data
 * will be the non-matching pin values. In the case of a buffered port,
 * this macro will wait until a non matching value appears on the pins, and
 * then return that value and previous values that have been deserialised.
 *
 * \param p      port variable that inidicates which port to input from
 * \param value  the value to match against the pins
 *
 * \returns      the input data shifted right by the transfer width
 *               of the port
 */
inline int port_input_shift_right_when_pinsneq(port p, int value)
{
  int data;
  asm volatile("setd res[%0],%1" :: "r" (p), "r" (value));
  asm volatile("setc res[%0],0x19" :: "r" (p));
  asm volatile("inshr %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Input data from a port when its counter is at a specific time  and shift the data.
 *
 *  In the case of an unbuffered port, the data will be inputted when the
 *  counter reaches time ``t``. In the case of a buffered port, an input
 *  will wait until the given time and then will start capturing data,
 *  returning a value when the buffer is full.
 *
 * \param p      port variable that inidicates which port to input from
 * \param t      the time to do input
 *
 * \returns      the input data shifted right by the transfer width
 *               of the port
 *
 */
inline int port_input_shift_right_at_time(port p, int t)
{
  int data;
  asm volatile("setpt res[%0],%1" :: "r" (p), "r" (t));
  asm volatile("setc res[%0],0x11" :: "r" (p));
  asm volatile("inshr %0,res[%1]" : "=r" (data): "r" (p));
  return data;
}

/** Force an input on a buffered port.
 *
 *  The function will perform an input on a buffered port even if the buffer is
 *  only partially full.
 *
 *  \param      p    The port to do the input on
 *  \param[out] n    A variable to be filled with number of bits inputted
 *  \returns         The inputted data
 */
#ifdef __XC__
inline int port_force_input(port p, int &n)
{
  asm volatile("endin %0,res[%1]":"=r"(n),"r"(p));
  return port_input(p);
}
#else
inline int port_force_input(port p, int *n)
{
  asm volatile("endin %0,res[%1]":"=r"(*n):"r"(p));
  return port_input(p);
}
#endif

/** Get the timestamp of the last operation on a port.
 *
 *  This function gets the timestamp of the last input or output operation
 *  on a port.
 *
 *  \param p   the port to get the timestamp from
 *  \returns   the timestamp of the last operation
 */
inline int port_get_timestamp(port p) {
  int ts;
  asm volatile("getts %0,res[%1]":"=r"(ts):"r"(p));
  return ts;
}

/** Type representing port conditions
 *
 *
 */
typedef enum port_condition_t {
  XS1_PORT_PINSEQ = 0x11,  //< Condition that holds when the pins of the port are equal to the port conditional data
  XS1_PORT_PINSNEQ = 0x19  //< Condition that holds when the pins of the port are equal to the port conditional data
} port_condition_t;

/** Set the condition on a port.
 *
 *  This sets the condition on a port. This condition will apply to all
 *  future inputs or outputs on
 *  a buffered port until the condition is set again.
 *  On a non-buffered port the condition will only hold for the next input or
 *  output after which the condition will be reset.
 *
 *  \param p  the port to set the condition on
 *  \param c  the condition
 *
 *  \sa port_set_conditional_data
 */
inline void port_set_condition(port p, port_condition_t c)
{
  asm volatile("setc res[%0],%1" :: "r" (p),"r"(c));
}

/** Set the conditional data on a port.
 *
 *  This sets the conditional data on a port.
 *  This should be used in conjunction with port_set_condition()
 *
 *  \param p  the port to set the condition on
 *  \param d  the conditional data
 */
inline void port_set_conditional_data(port p, int d)
{
  asm volatile("setd res[%0],%1" :: "r" (p),"r"(d));
}

/** Set the time condition on a port
 *
 *  This function sets the time condition on the next input or output on
 *  a port.
 *
 *  \param p the port to set the condition on
 *  \param t the time
 *
 */
inline void port_set_time_condition(port p, int t)
{
  asm volatile("setpt res[%0],%0" :: "r" (p),"r"(t));
}

/** Clear the condition on a port.
 *
 *  This function clears any condition on the port so the next input or
 *  output will happen unconditionally. This function does not clear
 *  any time condition on the port.
 *
 * \param p the port to clear the condition on
 *
 */
inline void port_clear_condition(port p)
{
  asm volatile("setc res[%0],0x1" :: "r" (p));
}

/** Clear the time condition on a port.
 *
 *  This function clears any time condition on the port so the next input or
 *  output will happen unconditionally. This function does not clear
 *  any non-time condition on the port.
 *
 * \param p the port to clear the time condition on
 *
 */
inline void port_clear_time_condition(port p)
{
  asm volatile("clrpt res[%0]" :: "r" (p));
}

/** Clears the buffer used by a port.
 *
 * Any data sampled by the port which has not
 * been input by the processor is discarded. Any data output by the processor which
 * has not been driven by the port is discarded. If the port is in the process
 * of serialising output, it is interrupted immediately.
 * If a pending output would have caused a change in direction of the port then
 * that change of direction does not take place. If the port is driving a value
 * on its pins when this function is called then it continues to drive
 * the value until an output statement changes the value driven.
 * \param p The port whose buffer is to be cleared.
 */
void port_clear_buffer(port p);

/** Ends the current input on a buffered port.
 *
 * The number of bits sampled by the
 * port but not yet input by the processor is returned. This count includes both
 * data in the transfer register and data in the shift register used for
 * deserialisation.
 * Subsequent inputs on the port return transfer-width bits of data
 * until there is less than one transfer-width bits of data remaining.
 * Any remaining data can be read with one further input, which
 * returns transfer-width bits of data with the remaining buffered data
 * in the most significant bits of this value.
 * \param p The port to end the current input on.
 * \return The number of bits of data remaining.
 */
unsigned port_endin(port p);




#endif
