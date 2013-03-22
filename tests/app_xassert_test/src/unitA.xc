#include <xassert.h>

void f()
{
#ifdef TEST_ASSERT
  assert(1 < 2);
  assert(1 > 2 && _msg("1 is bigger than 2 isn't it?"));
#endif

#ifdef TEST_FAIL
  fail("This is a failure in unitA");
#endif

#ifdef TEST_UNREACHABLE
  unreachable("This is unreachable in unitA");
#endif
}
