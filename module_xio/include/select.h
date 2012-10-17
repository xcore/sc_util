#ifndef __select_h__
#define __select_h__

enum select_control {
  SELECT_END = -1,
  SELECT_DEFAULT = -2,
  SELECT_OVER_ARRAY = -3,
  SELECT_WHEN_PINSEQ = -4,
  SELECT_WHEN_PINSNEQ = -5,
  SELECT_WHEN_TIMERAFTER = -6,
  SELECT_AT_TIME = -7,
  SELECT_GUARD = -8
};

int __c_select(int x, ...);
int __c_ordered_select(int x, ...);

#ifdef __DOXYGEN__


/** Predicate to select only if port pins are equal to a value.
 *
 *  This function alters the port to only cause a select
 *  to fire on that port if the ports pins match a given value.
 *  It can be used in a select in the following manner:
 *
 *  \code
 *    res = select(...,when_pinseq(p, 5),...)
 *  \endcode
 *
 *  \param p     the port resource to select on
 *  \param value the value to match against the pins
 */
when_pinseq(port p, int value);

/** Predicate to select only if port pins are not equal to a value.
 *
 *  This function alters the port to only cause a select
 *  to fire on that port if the ports pins do not match a given value.
 *  It can be used in a select in the following manner:
 *
 *  \code
 *    res = select(...,when_pinsneq(p, 5),...)
 *  \endcode
 *
 *  \param p     the port resource to select on
 *  \param value the value to match against the pins
 */
when_pinsneq(port p, int value);

/** Predicate to select only if port pins is at a particular time.
 *
 *  This function alters the port to only cause a select
 *  to fire on that port if the ports counter is at a particular time value:
 *
 *  \code
 *    res = select(...,when_at_time(p, 5),...)
 *  \endcode
 *
 *  Please note that if you are using this for a buffered port and the port
 *  does not event, you will need to clear the time condition on that port using
 *  port_clear_time_condition().
 *
 *  \param p     the port resource to select on
 *  \param time  the specified time when the port should event
 */
when_at_time(port p, int time);


/** Predicate to select only if a timer is after a specified.
 *
 *  This function alters a timer to only cause a select
 *  to fire on that timer is after a particular time. It can be used
 *  in a select in the following manner:
 *
 *  \code
 *    res = select(...,when_timerafter(t, time),...)
 *  \endcode
 *
 *
 *  \param t     the timer resourcpe to select on
 *  \param time  the specified time after which the timer should event
 */
when_timerafter(timer t, int time);

/** A default case within a select.
 *
 *  This macro value can be used within a select to specify a *default* case.
 *  If none of the other resources of the select are ready to event when the
 *  select is called then the default case will activate and the select will
 *  return with the value of the argument index of the ``SELECT_DEFAULT``
 *  argument.
 *
 *  For example, in the following call:
 *
 *  \code
 *  res = select(a, b, SELECT_DEFAULT)
 *  \endcode
 *
 *  If resources ``a`` and ``b`` are not ready to event then the select will
 *  return will value 2 (since the argument of the ``SELECT_DEFAULT`` is at
 *  index 2).
 *
 *  If two or more ``SELECT_DEFAULT`` arguments are passed to a select then
 *  the behaviour is undefined.
 */
#define SELECT_DEFAULT

/** Select over an array of resources in the select case.
 *
 *  This function can be used in #define SELECT_DEFAULT
 a select to add an array of resources to the
 *  select. If any of the resources in the select events then the select will
 *  return the index of the ``select_over_array`` argument in the select.
 *  To determine which array element caused the select to fire you can call
 *  the get_selected_array_index() function.
 *
 *  For example, in the following code:
 *
 *  \code
 *  res = select(a, select_over_array(b,5), c);
 *  \endcode
 *
 *  If one of the resources in the array ``b[]`` events then the select would
 *  return 1 and get_selected_array_index() will return an index between ``0``
 *  and ``4``.
 *
 *  \param arr  The array of resources to select over
 *  \param n  The size of the array
 */
select_over_array(arr[], int n);


/** Only enable a select case if a guard expression is true.
 *
 *  This function is used within a select to only fire on an event if the
 *  given value is true. For example, in the following code:
 *
 *  \code
 *  res = select(a, select_only_if(x<5,b), c);
 *  \endcode
 *
 *  If ``x < 5`` evaluates to non-zero at the time of calling the select then
 *  resource ``b`` will be monitored for an event to occur. If ``x < 5``
 *  evaluates to 0 then ``b`` cannot cause the select to return.
 *
 *  Note that if the guard is false, the indexing is unaffected. In the
 *  above example, if ``x<5`` is false and ``c`` is selected then the select
 *  will still return ``2``.
 *
 *  \param guard  a value that will disable the select case if 0
 *  \param x      the resource to select with if the guard is true
 */
select_only_if(int guard, x);

#endif

#define select(...) __c_select(__VA_ARGS__, SELECT_END)

#define select_over_array(a, n) SELECT_OVER_ARRAY,a,n

#define when_pinseq(p, d) SELECT_WHEN_PINSEQ, p, d

#define when_pinsneq(p, d) SELECT_WHEN_PINSNEQ, p, d

#define when_at_time(p, d) SELECT_AT_TIME, p, d

#define when_timerafter(p, d) SELECT_WHEN_TIMERAFTER, p, d

#define select_only_if(e, x) SELECT_IF, e, x


/** Return the index of a select array element.
 *
 *  This function is to be used in conjunction with select_over_array().
 *  If an array is selected then this function will return the index of the
 *  resource within that array that caused the event.
 */
int get_selected_array_index();

#endif
