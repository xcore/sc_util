Random number generation module
===============================

This module provides a random number generator that can be seeded from
the hardware. The module can be used by including ``module_random`` in
the ``USED_MODULES`` variable in an application Makefile and then
including the ``random.h`` header.

The random number generator uses a CRC for generation which is
fast in terms of performance and code size and produces reasonably
good random numbers.  The generation algorithm is equivalent to a
Linear Feedback Shift Registor and has a cycle of 2 :sup:`32`.

API
---

Configuration defines can be set by creating a file called
``random_conf.h`` in the application that uses the module.

The module works by creating generators of type
``random_generator_t``. These generators can be used to create random
numbers (which updates the state of the generator.

.. doxygentypedef:: random_generator_t

.. doxygenfunction:: random_create_generator_from_seed
.. doxygenfunction:: random_create_generator_from_hw_seed
.. doxygenfunction:: random_get_random_number

For hardware generated seed the following define should be used:

 .. doxygendefine:: RANDOM_ENABLE_HW_SEED
