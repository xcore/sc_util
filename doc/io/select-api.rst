Selection
---------

Selection is used to wait for an event to happen on one of several
resources.

Selects
.......

.. c:function:: select(...)

   Perform a selection over a set of resources.

   This macro is variadic and takes arguments which can be of type ``port``,
   ``timer`` or ``chanend``. The effect of the function is to wait for
   an event to happen on one of the resources. When an event occurs
   the function returns an integer representing the resource that the
   event occured on. The return value is *n* if the resource that evente
   d was the the *n*-th argument of the select function. For example,
   in the call::

     res = select(a, b, c);

   ``res`` would be 0 if the event occurred on resource `a`, 1 if it
   occurred on resource `b` and 2 if it occurred on resource `c`.


.. c:function:: ordered_select(...)

   Perform a prioritized selection over a set of resources.

   This macro is variadic and takes arguments which can be of type ``port``,
   ``timer`` or ``chanend``. The effect of the function is to wait for
   an event to happen on one of the resources in the same manner as a
   call to :c:func:`select`. However, with an ordered select a
   priority is applied such that if two resources are both ready to
   event, resource given as earlier arguments will be prioritized over
   later arguments.

Predicates
..........

.. doxygenfunction:: when_pinseq

.. doxygenfunction:: when_pinsneq

.. doxygenfunction:: when_at_time

.. doxygenfunction:: when_timerafter

The default case
................

.. doxygendefine:: SELECT_DEFAULT


Selecting over arrays
.....................

.. doxygenfunction:: select_over_array
.. doxygenfunction:: get_selected_array_index

Guarded select cases
....................

.. doxygenfunction:: select_only_if
