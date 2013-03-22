#include "random.h"
#include <xs1.h>

#if RANDOM_ENABLE_HW_SEED

__attribute__((constructor))
void random_simple_init_seed()
{
  setps(0x060b, 0x3);
}

#endif
