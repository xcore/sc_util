#ifndef __xassert_h__
#define __xassert_h__

/****
xassert Module
==============

This module provides a lightweight and flexible replacement for the
standard C header ``assert.h``.

The assertions in this module can be enabled/disabled
and configured as to how much debug information they show. This
configuration can be per "debug unit" (i.e. for sets of files).

To use the module you need to use ``module_xassert`` in your application and
include the ``xassert.h`` header.

Assertions
----------

An assertion can be inserted into code with the ``assert`` macro e.g.::

   assert(i < n);

Optionally a debug message can be added with the ``msg`` macro::

   assert(i < n && msg("i must be less than the array bound"));

If assertions are enabled and the expression in the assertion is false than a
trap will occur.

Unreachable
-----------

If the logic of a program dictates that certain code cannot be reached, the
``unreachable`` macro can be used e.g.::

  switch (message) {
  case 0:
     ...
  case 1:
     ...
  default:
    unreachable("message must be 0 or 1");
    break;
  }

If assertions are enabled then this macro will cause a trap if executed.

Fail
----

A failure can be indicated with the ``fail`` macro e.g.::

  if (reg_value != 0xA5)
    fail("device not connected properly")

A fail will always cause a trap if executed. A failure differs from
unreachable in that an unreachable macro should never execute in a
correct program whereas a fail could happen in catastrophic circumstances
even if the program is correct.

Controlling assertions
----------------------

Assertions can be enabled/disabled in ``debug_conf.h`` in your application with the following defines.

XASSERT_ENABLE_ASSERTIONS
  This define can be used to turn assertions on or off (defaults to 1).

XASSERT_ENABLE_DEBUG
  This define will cause assertions to print out the failing expression before
  trapping (defaults to 0). Note that this option could significantly increase
  the code size of your application.

XASSERT_ENABLE_LINE_NUMBERS
  This define will cause assertions to print the file and line number of the
  assertion before trapping. Note that this option could significantly increase
  the code size of your application.

If ``DEBUG_UNIT`` is defined when ``xassert.h`` is included then all the
assertions in that file belong to that unit. Assertions can then be
controlled per debug unit. The mechanism is similar to that used in
``module_logging``.

XASSERT_ENABLE_ASSERTIONS_[debug unit]
   Enable asserts for a particular debug unit. If set to 1,
   this overrides the default set by ``XASSERT_ENABLE_ASSERTIONS`` for
   that debug unit.

XASSERT_ENABLE_DEBUG_[debug unit]
   Enable debug messages for a particular debug unit.  If set to 1,
   this overrides the default set by ``XASSERT_ENABLE_DEBUG`` for that
   debug unit .

XASSERT_DISABLE_ASSERTIONS_[debug unit]
   Disable asserts for a particular debug unit. If set to 1,
   this overrides the default set by ``XASSERT_ENABLE_ASSERTIONS`` for
   that debug unit.

XASSERT_DISABLE_DEBUG_[debug unit]
   Disable debug messages for a particular debug unit.  If set to 1,
   this overrides the default set by ``XASSERT_ENABLE_DEBUG`` for that
   debug unit .


 ****/

#ifdef __xassert_conf_h_exists__
#include "xassert_conf.h"
#endif

#ifdef __debug_conf_h_exists__
#include "debug_conf.h"
#endif

#ifndef DEBUG_UNIT
#define DEBUG_UNIT APPLICATION
#endif

#ifndef XASSERT_ENABLE_ASSERTIONS
#define XASSERT_ENABLE_ASSERTIONS 1
#endif

#ifndef XASSERT_ENABLE_DEBUG
#define XASSERT_ENABLE_DEBUG 0
#endif

#ifndef XASSERT_ENABLE_LINE_NUMBERS
#define XASSERT_ENABLE_LINE_NUMBERS 0
#endif

#define XASSERT_JOIN0(x,y) x ## y
#define XASSERT_JOIN(x,y) XASSERT_JOIN0(x,y)

#if XASSERT_JOIN(XASSERT_ENABLE_ASSERTIONS_,DEBUG_UNIT)
#  define XASSERT_ENABLE_ASSERTIONS0 1
#endif

#if XASSERT_JOIN(XASSERT_DISABLE_ASSERTIONS_,DEBUG_UNIT)
#  define XASSERT_ENABLE_ASSERTIONS0 0
#endif

#if !defined(XASSERT_ENABLE_ASSERTIONS0)
#  define XASSERT_ENABLE_ASSERTIONS0 XASSERT_ENABLE_ASSERTIONS
#endif

#if XASSERT_JOIN(XASSERT_ENABLE_DEBUG_,DEBUG_UNIT)
#  define XASSERT_ENABLE_DEBUG0 1
#endif

#if XASSERT_JOIN(XASSERT_DISABLE_DEBUG_,DEBUG_UNIT)
#  define XASSERT_ENABLE_DEBUG0 0
#endif

#if !defined(XASSERT_ENABLE_DEBUG0)
#  define XASSERT_ENABLE_DEBUG0 XASSERT_ENABLE_DEBUG
#endif

#if XASSERT_ENABLE_DEBUG0
#  include "print.h"
#endif

#if XASSERT_ENABLE_LINE_NUMBERS
#  define xassert_print_line do { printstr(" (" __FILE__ ":");    \
                                  printint(__LINE__);         \
                                  printstrln(")");            \
                                } while(0)
#else
#  define xassert_print_line do { printstrln(""); } while(0)
#endif


#if XASSERT_ENABLE_ASSERTIONS0
#  if XASSERT_ENABLE_DEBUG0
#    define xassert(e) do { if (!(e)) {\
       printstr(#e); xassert_print_line; \
      __builtin_trap();} \
      } while(0)
#  else
#    define xassert(e) do { if (!(e)) __builtin_trap();} while(0)
#  endif
#else
#  define xassert(e)   // disabled
#endif

#if XASSERT_ENABLE_ASSERTIONS0
#  if XASSERT_ENABLE_DEBUG0
#    define unreachable(msg) do { printstr(msg); xassert_print_line; __builtin_trap();} while(0)
#  else
#    define unreachable(msg) do { __builtin_trap();} while(0)
#  endif
#else
#  define unreachable(msg) do { __builtin_unreachable();} while(0)
#endif

#if XASSERT_ENABLE_DEBUG0
#  define fail(msg) do { printstr(msg); xassert_print_line; __builtin_trap();} while(0)
#else
#  define fail(msg) do { __builtin_trap();} while(0)
#endif

inline int xassert_msg(const char msg[]) { return 1; }

#ifdef __XC__
#define _msg(x) xassert_msg(x)
#define  msg(x) xassert_msg(x)
#else
#define _msg(x) x
#define  msg(x) x
#endif

#if !defined(assert) && !XASSERT_DISABLE_ASSERT_DEF
#define assert(...) xassert(__VA_ARGS__)
#endif

#endif // __xassert_h__
