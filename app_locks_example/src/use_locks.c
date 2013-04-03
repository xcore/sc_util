#include "hwlock.h"
#include "swlock.h"
#include <stdio.h>

int a[5];
int b[5];

hwlock_t hwlock;
swlock_t swlock = SWLOCK_INITIAL_VALUE;

static void process_array(int a[], int n, int mult)
{
  for (int i = 0; i < n; i++) {
    a[i] = i * mult;
  }
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  puts("");
}

void init_locks(void)
{
  hwlock = hwlock_alloc();
}

void free_locks(void)
{
  hwlock_free(hwlock);
}

void use_hwlock(int mult)
{
  hwlock_acquire(hwlock);
  process_array(a, 5, mult);
  hwlock_release(hwlock);
}

void use_swlock(int mult)
{
  swlock_acquire(&swlock);
  process_array(b, 5, mult);
  swlock_release(&swlock);
}

