#ifndef C_TIMER_H

#define C_TIMER_H
#include <xccompat.h>


/** Allocates and initialise a timer. This macro is to be
 * called once on every variable of the type ``timer``.
 * If there are no timers availble, then the function will return NULL.
 * When the timer is no longer required, timer_free() should be called
 * to free the timer.
 *
 * \returns the initialized timer
 */
inline timer timer_alloc(void)
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
inline void timer_free(timer t)
{
  asm volatile("freer res[%0]" :: "r" (t));
}

/** Get the current time from the timer.
 *
 * \param t    timer on which to input
 * \returns    the 32-bit time.
 */
inline int timer_get_time(timer t)
{
  int i;
  asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));
  return i;
}


/** Pause until after a specified time
 *
 *  \param tmr  the timer to use for timing
 *  \param time the time to wait until
 *
 */
inline int timer_wait_until(timer tmr, int time)
{
  asm volatile("setd res[%0],%1" :: "r" (tmr), "r" (time));
  asm volatile("setc res[%0],9" :: "r" (tmr));
  return timer_get_time(tmr);
}

/** Delay for a specified time. This function pauses until the time is
 *  reached.
 *
 *  \param period    The amount of time to wait (in reference time ticks,
 *                   usually 10ns steps)
 */
inline void delay(int period)
{
  timer tmr = timer_alloc();
  int time;
  time = timer_get_time(tmr);
  time += period;
  timer_wait_until(tmr, time);
  timer_free(tmr);
}

/** Delay for a specified time using a specific timer.

 *  This function pauses until the time is
 *  reached.
 *
 *  \param tmr       The timer resource to use
 *  \param period    The amount of time to wait (in reference time ticks,
 *                   usually 10ns steps)
 */
inline void timer_delay(timer tmr, int period)
{
  int time;
  time = timer_get_time(tmr);
  time += period;
  timer_wait_until(tmr, time);
}

#endif
