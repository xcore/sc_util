#define DEBUG_UNIT A
#include "debug_print.h"

void f() {
  debug_printf("Unit A\n");
  debug_printf("Int: %d\n",-5);
  debug_printf("Unsigned: %u\n",5);
  debug_printf("Hex: %x\n",500);
  debug_printf("String: %s\n","hello world");
  debug_printf("Char: %c\n",'a');

  debug_printf("Zero: %d\n",0);
  debug_printf("Large uint: %u\n",0xffffffff);
  debug_printf("Large hex: %x\n",0xffff0000);
}
