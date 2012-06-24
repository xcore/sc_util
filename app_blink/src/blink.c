#include <xs1.h>
#include "platform.h"
#include "cxc.h"

int main() {
  port p;

  p = port_init(XS1_PORT_4F);
  while (1) {
    output_data(p, 1);
    delay(1000);
    output_data(p, 0);
    delay(1000);
  }
  port_exit(p);
}
