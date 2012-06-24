#ifndef C_TIMER_H

#define C_TIMER_H
#include <xccompat.h>


/** Allocates and initialise a timer. This macro is to be
 * called once on every variable of the type ``timer``.
 * If there are no timers availble, then the function will return NULL.
 * When the timer is no longer required, timer_exit() should be called
 * to free the timer.
 *
 * \returns the initialized timer
 */
inline timer timer_init(void)
{
  timer t;
  asm volatile("getr %0,1" : "=r" (t));
  return t;
}


/** Deallocate a timer. This function is to be
 * called once on every variable of the type ``timer``.
 *
 * \param t timer to be freed
 */
inline void timer_exit(timer t)
{
  asm volatile("freer res[%0]" :: "r" (t));
}

/** Get the current time from the timer.
 *
 * \param t    timer on which to input
 * \returns    the 32-bit time.
 */
inline int get_time(timer t)
{
  int i;
  asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));
  return i;
}


/** Set a timer to only input after a specified time.
 *  This is usually used in cojunction with select() e.g.
 *
 *  \code
 *
 *    select(c, timer_when_timerafter(tmr, time));
 *
 *  \endcode
 *
 *  \param   timer   the time after which the timer can event/input
 *  \returns         the timer with the condition set
 *
 */
inline timer timer_when_timerafter(timer tmr, int time)
{
  asm volatile("setd res[%0],%1" :: "r" (tmr), "r" (time));
  asm volatile("setc res[%0],9" :: "r" (tmr));
  return tmr;
}

/** Pause until after a specified time
 *
 *  \input tmr  the timer to use for timing
 *  \input time the time to wait until
 */
inline void wait_until(timer tmr, int time)
{
  (void) get_time(timer_when_timerafter(tmr, time));
}

/** Delay for a specified time. This function pauses until the time is
 *  reached.
 *
 *  \input period    The amount of time to wait (in reference time ticks,
 *                   usually 10ns steps)
 */
inline void delay(int period)
{
  timer tmr = timer_init();
  int time;
  time = get_time(tmr);
  time += period;
  wait_until(tmr, time);
  timer_exit(tmr);
}

#endif
