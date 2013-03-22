#include "debug_print.h"
void f();
void g();

int main() {
  debug_printf("Main application message\n");
  f();
  g();
  return 0;
}
