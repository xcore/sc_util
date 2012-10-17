Channels
--------

There are two types of channels: streaming channels and normal channels.
The latter are safe and synchronised; the former are not sychronised and
keep a route through the switches open.

To use xcore channels from C, include the file ``channel.h``.

Types
=====

.. c:type:: chanend

  Type that denotes a channel-end. This type is inherited from ``xccompat.h``.

  Communication channels comprise two connected channel-ends and can be
  created using :c:func:`chan_alloc` Channels should be deinitialised
  using :c:func:`chan_free`.


.. doxygentypedef:: streaming_chanend

API
===

Synchronized Channel Operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Initialization
..............

.. doxygenfunction:: chan_alloc
.. doxygenfunction:: chan_free

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

.. doxygenfunction:: s_chan_alloc
.. doxygenfunction:: s_chan_free

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

Transactions
^^^^^^^^^^^^

.. doxygentypedef:: transacting_chanend


.. doxygenfunction:: chan_init_transaction_master
.. doxygenfunction:: chan_init_transaction_slave
.. doxygenfunction:: chan_complete_transaction

.. doxygenfunction:: t_chan_output_word
.. doxygenfunction:: t_chan_output_byte
.. doxygenfunction:: t_chan_output_ct
.. doxygenfunction:: t_chan_output_block


.. doxygenfunction:: t_chan_check_ct
.. doxygenfunction:: t_chan_input_word
.. doxygenfunction:: t_chan_input_byte
.. doxygenfunction:: t_chan_input_block




