#ifndef C_TIMER_H

#define C_TIMER_H

/** Type that denotes a timer. Variables of this type should be initalised
 * using timer_init(), and deinitialised using timer_exit().
 */
typedef unsigned int timer_t;

/** Macro that allocates and initialises a timer. This macro is to be
 * called once on every variable of the type ``timer_t``. If there are no timers availble, then ``t`` will be set to NULL.
 * When the timer is no longer required, timer_exit() should be called
 * to free the timer.
 *
 * \param t timer to be initialised
 */
void timer_init(timer_t t);
#define timer_init(t) \
    asm volatile("getr %0,1" : "=r" (t));


/** Macro that deallocates and initialises a timer. This macro is to be
 * called once on every variable of the type ``timer_t``.
 *
 * \param t timer to be freed
 */
void timer_exit(timer_t t);
#define timer_exit(t) \
    asm volatile("freer res[%0]" :: "r" (t));

/** Macro that inputs the current time from the timer. 
 *
 * \param t    timer on which to input
 * \param time variable in which to leave the 32-bit time.
 */
void timer_in(timer_t t, int time);
#define timer_in(t, i)                            \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));

/** Macro that inputs the current time from the timer, but only after a
 * specified time has been reached.
 *
 * \param t          timer on which to input
 * \param time       variable in which to leave the 32-bit time.
 * \param after_time time for which to wait
 */
void timer_in_when_timerafter(timer_t t, int time, int after_time);
#define timer_in_when_timerafter(t,i,v)              \
    asm volatile("setd res[%0],%1" :: "r" (t), "r" (v)); \
    asm volatile("setc res[%0],9" :: "r" (t));       \
    asm volatile("in %0,res[%1]" : "=r" (i): "r" (t));

#endif
