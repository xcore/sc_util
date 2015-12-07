sc_util Change Log
==================

1.0.6
-----
  * xCORE-200 compatibility fixes to module_trycatch

1.0.5
-----
  * xCORE-200 compatibility fixes to module_locks

1.0.4
-----
  * module_logging now compiled at -Os
  * debug_printf in module_logging uses a buffer to deliver messages unfragmented
  * Fix thread local storage calculation bug in libtrycatch
  * Fix debug_printf itoa to work for unsigned values > 0x80000000

1.0.3
-----
  * Remove module_slicekit_support (moved to sc_slicekit_support)
  * Update mutual_thread_comm library to avoid communication race conditions

1.0.2
-----
  * Fix module_slicekit_support to work with L16 target

1.0.1
-----
  * Fix to module_logging to remove excess warning and avoid compiler reserved _msg
  * Minor fixes and code tidying to lock module

1.0.0
-----
  * Initial Version
