C XCore Resources
'''''''''''''''''

Timers
------

Types
=====

.. doxygentypedef:: type_t

API
===

.. doxygenfunction:: timer_init
.. doxygenfunction:: timer_exit
.. doxygenfunction:: timer_in
.. doxygenfunction:: timer_in_when_timerafter

Example
=======


An example program is shown below::

  TBC.


Channels
--------

There are two types of channels: streaming channels and normal channels.
The latter are safe and synchronised; the former are not sychronised and
keep a route through the switches open.

Types
=====

.. doxygentypedef:: chanend_t
.. doxygentypedef:: streaming_chanend_t

API
===

.. doxygenfunction:: schan_init
.. doxygenfunction:: chan_init
.. doxygenfunction:: chan_exit
.. doxygenfunction:: schan_exit
.. doxygenfunction:: schan_outct
.. doxygenfunction:: schan_chkct
.. doxygenfunction:: schan_out_int
.. doxygenfunction:: schan_in_int
.. doxygenfunction:: chan_out_int
.. doxygenfunction:: chan_in_int

Example
=======

An example program is shown below::

  TBC.


Ports
-----


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

An example program is shown below::

  TBC.


Threads
-------

Types
=====


API
===


Example
=======

An example program is shown below::

  TBC.

