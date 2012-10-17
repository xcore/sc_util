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

.. doxygentypedef:: timer

API
===

.. doxygenfunction:: timer_init
.. doxygenfunction:: timer_exit
.. doxygenfunction:: timer_get_time
.. doxygenfunction:: timer_wait_until
.. doxygenfunction:: timer_delay

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

Synchronized Channel Operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Initialization
..............

.. doxygenfunction:: chan_init
.. doxygenfunction:: chan_exit

Output
......

.. doxygenfunction:: chan_output_word
.. doxygenfunction:: chan_output_byte
.. doxygenfunction:: chan_output_block

Input
.....
.. doxygenfunction:: chan_input_word
.. doxygenfunction:: chan_input_byte
.. doxygenfunction:: chan_input_block

Streaming Channel Operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Initialization
..............

.. doxygenfunction:: s_chan_init
.. doxygenfunction:: s_chan_exit

Output
......

.. doxygenfunction:: s_chan_output_word
.. doxygenfunction:: s_chan_output_byte
.. doxygenfunction:: s_chan_output_ct
.. doxygenfunction:: s_chan_output_block

Input
.....

.. doxygenfunction:: s_chan_check_ct
.. doxygenfunction:: s_chan_input_word
.. doxygenfunction:: s_chan_input_byte
.. doxygenfunction:: s_chan_input_block

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

Threads
-------

To use threads from C, include the file ``thread.h``.

Types
=====

.. doxygentypedef:: thread_t
.. doxygentypedef:: thread_group_t

API
===

.. doxygenfunction:: thread_create
.. doxygenfunction:: thread_create_detached
.. doxygenfunction:: thread_join
.. doxygenfunction:: thread_exit
.. doxygenfunction:: thread_group_create
.. doxygenfunction:: thread_create_in_group
.. doxygenfunction:: thread_group_start
.. doxygenfunction:: thread_sync
.. doxygenfunction:: thread_group_sync
.. doxygenfunction:: thread_group_join

.. _sec_api_threads:

Example thread usage
====================

Example code that uses threads is shown below. First a channel is created.
A new thread is created that takes one end of the channel as an argument.
The new thread communciates over the channel. Finally the parent thread waits
for the new thread terminate and then frees the channel.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:thread main
   :end-before: //:thread end main

Example code which uses thread groups is shown below. Here a thread group is
created and two threads are created in that thread group. When started the two
threads print strings using the printstr() function. The threads synchronize
using thread_sync() and thread_group_sync() to ensure the strings are printed
in the correct order.

.. literalinclude:: app_c_example/src/main.c
   :start-after: //:thread_group main
   :end-before: //:thread_group end main
