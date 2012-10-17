Slicekit Core Board Support Library
===================================

:scope: General Use
:description: A library for configuring the sliceKIT Core Board ports
:keywords: slicekit, spi

This module runs a some initial code on booting to configure the ports
for the sliceKIT Core Board to either route ports 1A,1B,1C and 1D on
tile[0] to the SPI flash during the application or to the STAR and
TRIANGLE slice card slots.

To use the module just include it in the USED_MODULES list in your
application makefile.

The default is to route the ports to the slice card slots. SPI Flash
will still work for booting but cannot be accessed during the
application. To route these ports to flash during the application
create a ``slicekit_conf.h`` file in your application and set the
following define::

  #define SLICEKIT_ENABLE_FLASH 1

If you do enable flash, then clearly you will not be able to access
the pins on the slice cards connected to these ports.

If this module is used when the application target is not
``SLICEKIT-L2`` then this module will do nothing.
