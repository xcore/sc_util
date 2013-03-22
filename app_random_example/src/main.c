#include <stdio.h>
#include <random.h>
#include <print.h>

int main(void)
{
  random_generator_t gen = random_create_generator_from_hw_seed();

  printf("%08x\n", random_get_random_number(&gen));
  printf("%08x\n", random_get_random_number(&gen));
  printf("%08x\n", random_get_random_number(&gen));

  gen = random_create_generator_from_seed(12345);

  printf("%08x\n", random_get_random_number(&gen));
  printf("%08x\n", random_get_random_number(&gen));
  printf("%08x\n", random_get_random_number(&gen));

  return 0;
}
