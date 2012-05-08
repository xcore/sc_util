C XCore Resources
'''''''''''''''''

The module c_xcore_resources is intended to provide low level access to all
XCore features from C. This library is intended to ease porting of legacy
software. Note that since C is not resource aware, the compiler cannot
analyse and optimise resource access to the same depth as the XC compiler. 

Timers
------

To use xcore timers from C, include the file ``timer.h``.

Types
=====

.. doxygentypedef:: timer_t

API
===

.. doxygenfunction:: timer_init
.. doxygenfunction:: timer_exit
.. doxygenfunction:: timer_in
.. doxygenfunction:: timer_in_when_timerafter

Example
=======

Example code that uses timers is shown below. A timer is declared, and
initialised. After that, the timer value is input, whereupon the code waits
for 100 reference clock ticks.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:timer main
   :end-before: //:timer end


Channels
--------

There are two types of channels: streaming channels and normal channels.
The latter are safe and synchronised; the former are not sychronised and
keep a route through the switches open.

To use xcore channels from C, include the file ``chan.h``.

Types
=====

.. doxygentypedef:: chanend_t
.. doxygentypedef:: streaming_chanend_t

API
===

.. doxygenfunction:: chan_init
.. doxygenfunction:: chan_exit
.. doxygenfunction:: chan_out_int
.. doxygenfunction:: chan_in_int
.. doxygenfunction:: schan_init
.. doxygenfunction:: schan_exit
.. doxygenfunction:: schan_outct
.. doxygenfunction:: schan_chkct
.. doxygenfunction:: schan_out_int
.. doxygenfunction:: schan_in_int

Example
=======

An example program is shown in :ref:`sec_api_threads`.


Ports
-----

To use xcore ports from C, include the file ``port.h``.

Types
=====

.. doxygentypedef:: port_t

API
===

.. doxygenfunction:: port_init
.. doxygenfunction:: port_init_buffered
.. doxygenfunction:: port_exit
.. doxygenfunction:: port_out
.. doxygenfunction:: port_in
.. doxygenfunction:: port_in_when_pinseq
.. doxygenfunction:: port_in_when_pinsneq

Example
=======

Example code that uses ports is shown below. This piece of code uses two
ports, ``x`` and ``y``. Each of the ports is initialised: ``x`` is
initialised as ``PORT_1A (pin X0D0 on an L1, see the datasheet); ``y`` is
initialised as a buffered port that serialises 32 bits of data, and is on
``PORT_1B`` (pin X0D1 on an L1). Both ports are used as output ports only,
and the sequence high, low, high is output to port ``x`` in short succession.
After that, 64 pulses are output onto port ``y`` (4 times 32 bits of data,
each 32 bits comprising a sequence ``1010101..10``).

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:port main
   :end-before: //:port end



Asynchronous Threads
--------------------

This module supports asynchronous threads, that is, threads that are
started and then run independently until they terminate themselves.

To use asynchronous XCore threads from C, include the file ``athread.h``.

Types
=====

.. doxygentypedef:: athread_t

API
===

.. doxygenfunction:: athread_init

.. doxygenfunction:: athread_exit

.. _sec_api_threads:

Example thread usage
====================

An example program is shown below. We first declare some channels for
communciation.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:athread chan
   :end-before: //:athread end chan

Then we declare two functions that embody the threads. In this case the
functions perform some trivial function, and then exit. Note that the
functions should not and do not return.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:athread funcs
   :end-before: //:athread end funcs

Finally to start the thread we call ``athread_init()`` twice. Prior to that
we initialise the channels, so that we can communicate with the threads
that have been created.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:athread main
   :end-before: //:athread end main


Synchronous Threads
-------------------

This module supports synchronous threads, that is, threads that start and
join synchronously. To this end, a *synchroniser* resource is used that
describes a group of threads.

To use synchronous XCore threads from C, include the file ``sthread.h``.

Types
=====

.. doxygentypedef:: sthread_t
.. doxygentypedef:: sthread_sync_t

API
===

.. doxygenfunction:: sthread_sync_init
.. doxygenfunction:: sthread_init
.. doxygenfunction:: sthread_start
.. doxygenfunction:: sthread_exit
.. doxygenfunction:: sthread_join

Example thread usage
====================


.. literalinclude:: app_c_example/src/main.c
   :start-after: //:sthread main
   :end-before: //:sthread end main

