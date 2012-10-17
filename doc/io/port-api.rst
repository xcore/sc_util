Ports
-----

To use xcore ports from C, include the file ``port.h``.

Types
=====

.. c:type:: port

   Type that denotes an XCore port resource.

   This type is inherited from ``xccompat.h`` and denotes both
   buffered and unbuffered ports. It can be used to interpoerate with
   XC functions that use the XC ``port`` type.

High-Level API
==============

Initialization
..............

.. doxygenfunction:: port_enable
.. doxygenfunction:: port_enable_buffered
.. doxygenfunction:: port_disable

Output
......

.. doxygenfunction:: port_output
.. doxygenfunction:: port_output_at_time

.. doxygenfunction:: port_output_shift_right
.. doxygenfunction:: port_output_shift_right_at_time

Input
.....

.. doxygenfunction:: port_input
.. doxygenfunction:: port_input_when_pinseq
.. doxygenfunction:: port_input_when_pinsneq
.. doxygenfunction:: port_input_at_time

.. doxygenfunction:: port_input_shift_right
.. doxygenfunction:: port_input_shift_right_when_pinseq
.. doxygenfunction:: port_input_shift_right_when_pinsneq
.. doxygenfunction:: port_input_shift_right_at_time

.. doxygenfunction:: port_force_input

Timestamps
..........

.. doxygenfunction:: port_get_timestamp

Low-Level API
=============

.. doxygenenum:: port_condition_t

.. doxygenfunction:: port_set_condition
.. doxygenfunction:: port_set_conditional_data
.. doxygenfunction:: port_set_time_condition
.. doxygenfunction:: port_clear_condition
.. doxygenfunction:: port_clear_time_condition
.. doxygenfunction:: port_clear_buffer
.. doxygenfunction:: port_endin

