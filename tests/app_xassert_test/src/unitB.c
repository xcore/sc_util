#include <xassert.h>

void g()
{
#ifdef TEST_MULTI_UNIT
  assert(1 < 2);
  assert(1 > 2 && msg("1 is bigger than 2 isn't it? (unitB)"));
#endif
}
