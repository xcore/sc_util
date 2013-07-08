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
__slicekit_init:
  // Only run this on tile[0]
  bl get_local_tile_id
  mov r4, r0
  ldaw r11, cp[tile]
  ldc r0, 0
  ld16s r0, r11[r0]
  zext r0, 16
  bl get_tile_id
  eq r0, r0, r4
  bf r0, .Lskip

__slicekit_init_handle_flash:
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
#if SLICEKIT_ENABLE_FLASH
  ldc r1, 0x1
#else
  ldc r1, 0x3
#endif
  shl r1, r1, 6
  out res[r11],r1
  syncr res[r11]
  ldc r1,15
.Lloop:
  sub r1,r1,1
  bt r1, .Lloop

  // Turn port 8D off
  setc res[r11], XS1_SETC_INUSE_OFF


.Lskip:

