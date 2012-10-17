#ifndef __xio_clock_h__
#define __xio_clock_h__
#include "xccompat.h"

/** Enable a clock.
 *
 *  This function enables a specified clock block and returns a clock
 *  variable denoting the clock.
 *
 *  \param clock_id   The id of the clock to enable
 */
clock clock_enable(int clock_id);

/** Disable a clock
 *
 *  \param clk  The clock to disable
 */
void clock_disable(clock clk);

/** Start a clock
 *
 *  This function starts a clock running.
 *
 *  \param clk  the clock to start running
 */
void clock_start(clock clk);

/** Stop a clock
 *
 *  This function pauses a clock.
 *
 *  \param clk the clock to stop
 */
void clock_stop(clock clk);


#endif // __xio_clock_h__
