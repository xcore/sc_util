Lock handling library
=====================

This module provides access to hardware and software locks for use in
concurrent C programs. In general it is not safe to use these to
marshall within XC due to the assumptions XC
makes about safe concurrent data access.

Two types of locks are provided. Hardware locks are fast and power
efficient but there are a limited number per tile. Software locks are
slower but you can use an unlimited number of them.

Hardware lock API
-----------------

.. doxygentypedef:: hwlock_t

.. doxygenfunction:: hwlock_alloc
.. doxygenfunction:: hwlock_free
.. doxygenfunction:: hwlock_acquire
.. doxygenfunction:: hwlock_release

Software lock API
-----------------

.. doxygentypedef:: swlock_t

.. doxygendefine:: SWLOCK_INITIAL_VALUE

.. doxygenfunction:: swlock_init
.. doxygenfunction:: swlock_try_acquire
.. doxygenfunction:: swlock_acquire
.. doxygenfunction:: swlock_release
