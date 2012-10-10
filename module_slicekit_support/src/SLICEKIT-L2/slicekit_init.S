#ifdef __slicekit_conf_h_exists__
#include "slicekit_conf.h"
#endif
#ifndef SLICEKIT_ENABLE_FLASH
#define SLICEKIT_ENABLE_FLASH 0
#endif

#include <xs1.h>

.section        .cp.rodata.cst4,"aMc",@progbits,4
        .align  4
.Lport8d:
        .long   XS1_PORT_8D
.section .init, "ax", @progbits

  // Only run this on tile[0]
  bl get_local_tile_id
  bt r0, .Lskip

  // Enable the clock and port required for doing the output
  ldc r11, _default_clkblk
  setc res[r11], XS1_SETC_INUSE_ON
  setc res[r11], XS1_SETC_RUN_STARTR
  mov r0, r11

  ldw r11, cp[.Lport8d]
  setc res[r11], XS1_SETC_INUSE_ON
  setclk res[r11], r0

  // Output whether to enable flash on 8D7 (D43) and then
  // move 8D6 (D42) high. This will latch the flash ports to be
  // either directed to flash or to the slice slots
  ldc r1, SLICEKIT_ENABLE_FLASH
  ldc r2, 7
  shl r1, r1, 7
  out res[r11], r1
  syncr res[r11]

  ldc r2, 1
  shl r2, r2, 6
  or  r1, r1, r2
  out res[r11], r1
  syncr res[r11]

  // Turn port 8D off
  setc res[r11], XS1_SETC_INUSE_OFF


.Lskip:

