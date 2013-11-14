#ifndef _debug_printf_h_
#define _debug_printf_h_

/****
Debug Printing Module
=====================

This module provides a lightweight printf function that can be enabled
or disabled via configuration macros. Code can be declared to be
within a "debug unit" (usually a module) and prints can be
enabled/disabled per debug unit.

API
---

To use this module, include ``module_logging`` in the application's
``USED_MODULES`` list and include the ``debug_print.h`` header file.

.. doxygenfunction:: debug_printf

Debug Units
-----------

A source file can be added to a debug unit by defining the ``DEBUG_UNIT`` macro before inclusion of ``debug_print.h``. For example::

  #define DEBUG_UNIT ETHERNET_MODULE
  #include "debug_print.h"

To include all source files in a module in a particular debug unit, it is
convenient to do it in the ``module_build_info`` file of the module e.g.::

  MODULE_XCC_FLAGS = $(XCC_FLAGS) -DDEBUG_UNIT=ETHERNET_MODULE

If no ``DEBUG_UNIT`` is defined then the default debug unit is ``APPLICATION``.

Enabling Printing
-----------------

By default, debug printing is turned *off*. To enable printing you
need to include a file called ``debug_conf.h`` in your application. Within this
file you can set the following defines:

DEBUG_PRINT_ENABLE
  Setting this define to 1 or 0 will control whether debug prints are output.

DEBUG_PRINT_ENABLE_[debug unit]
  Enabling this define will cause printing to be enabled for a specific
  debug unit. If set to 1, this will override the default set by
  ``DEBUG_PRINT_ENABLE``.

DEBUG_PRINT_DISABLE_[debug unit]
  Enabling this define will cause printing to be disabled for a specific
  debug unit. If set to 1, this will override the default set by
  ``DEBUG_PRINT_ENABLE``.

 ****/


#ifdef __debug_conf_h_exists__
#include "debug_conf.h"
#endif

#ifndef DEBUG_UNIT
#define DEBUG_UNIT APPLICATION
#endif

#ifndef DEBUG_PRINT_ENABLE
#define DEBUG_PRINT_ENABLE 0
#endif

#define DEBUG_UTILS_JOIN0(x,y) x ## y
#define DEBUG_UTILS_JOIN(x,y) DEBUG_UTILS_JOIN0(x,y)

#if DEBUG_UTILS_JOIN(DEBUG_PRINT_ENABLE_,DEBUG_UNIT)
#define DEBUG_PRINT_ENABLE0 1
#endif

#if DEBUG_UTILS_JOIN(DEBUG_PRINT_DISABLE_,DEBUG_UNIT)
#define DEBUG_PRINT_ENABLE0 0
#endif

#if !defined(DEBUG_PRINT_ENABLE0)
#define DEBUG_PRINT_ENABLE0 DEBUG_PRINT_ENABLE
#endif

/**  A limited functionality version of printf that is low memory.
 *
 *   This function works like C-standard printf except that it only accepts
 *    %d, %x, %s, %u and %c format specifiers with no conversions.
 *   The function uses the functions from ``print.h`` to do the
 *   underlying printing.
 *
 *   Unlike printf this function has no return value.
 *
 *   Whether the function does any output can be controlled via
 *   defines such as ``DEBUG_PRINT_ENABLE`` or
 *   ``DEBUG_PRINT_ENABLE_[debug unit name]``
 *   in the application's ``debug_conf.h``
 */
void debug_printf(char fmt[], ...);

#if DEBUG_PRINT_ENABLE0
#define debug_printf(...) debug_printf(__VA_ARGS__)
#else
#define debug_printf(...)
#endif



#endif // _debug_printf_h_
