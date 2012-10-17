Timers
------

To use xcore timers from C, include the file ``timer.h``.

Types
=====
.. c:type:: timer

   Type that denotes an xcore timer resource.

   This type is inherited from ``xccompat.h`` and is compatible with
   the XC ``timer`` type (i.e. functions in XC can pass a timer to
   function in C using this type). Timers should be initialized with
   :c:func:`timer_alloc` and when the resource is finished with
   :c:func:`timer_free` should be used.

API
===

.. doxygenfunction:: timer_alloc
.. doxygenfunction:: timer_free
.. doxygenfunction:: timer_get_time
.. doxygenfunction:: timer_wait_until
.. doxygenfunction:: delay
.. doxygenfunction:: timer_delay

