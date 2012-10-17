#include "thread.h"
#include <xs1.h>

#define QUOTEAUX(x) #x
#define QUOTE(x) QUOTEAUX(x)

static char is_detached[XS1_NUM_THREADS];

__attribute__((noreturn)) extern void joinable_thread_exit(void *value);
__attribute__((noreturn)) extern void detached_thread_exit(void);

int thread_create(thread_t *tPtr, void *(*fptr)(void *), void *stack,
                  unsigned num_stack_words, void *args)
{
  thread_t sync;
  unsigned t;
  asm volatile("getr %0, " QUOTE(XS1_RES_TYPE_SYNC) : "=r"(sync));
  if (!sync)
    return 1;
  asm volatile("getst %0, res[%1]" : "=r"(t) : "r"(sync));
  if (!t)
    return 1;
  is_detached[t >> XS1_RES_ID_RESNUM_SHIFT] = 0;
  asm volatile("init t[%0]:pc, %1" : /* no outputs*/ : "r"(t), "r"(fptr));
  asm volatile("init t[%0]:sp, %1" : /* no outputs*/ : "r"(t), "r"((int *)stack + num_stack_words - 1));
  asm volatile("init t[%0]:lr, %1" : /* no outputs*/ : "r"(t), "r"(&joinable_thread_exit));
  asm volatile("set t[%0]:r0, %1" : /* no outputs*/ : "r"(t), "r"(args));
  asm volatile("msync res[%0]" : /* no outputs*/ : "r"(sync) : "memory");
  *tPtr = sync;
  return 0;
}

int thread_create_detached(void *(*fptr)(void *), void *stack,
                           unsigned num_stack_words, void *args)
{
  unsigned t;
  asm volatile("getr %0, " QUOTE(XS1_RES_TYPE_THREAD) : "=r"(t));
  if (!t)
    return 1;
  is_detached[t >> XS1_RES_ID_RESNUM_SHIFT] = 1;
  asm volatile("init t[%0]:pc, %1" : /* no outputs*/ : "r"(t), "r"(fptr));
  asm volatile("init t[%0]:sp, %1" : /* no outputs*/ : "r"(t), "r"((int *)stack + num_stack_words - 1));
  asm volatile("init t[%0]:lr, %1" : /* no outputs*/ : "r"(t), "r"(&detached_thread_exit));
  asm volatile("set t[%0]:r0, %1" : /* no outputs*/ : "r"(t), "r"(args));
  asm volatile("start t[%0]" : /* no outputs*/ : "r"(t) : "memory");
  return 0;
}

int thread_group_create(thread_group_t *group)
{
  thread_group_t sync;
  asm volatile("getr %0, " QUOTE(XS1_RES_TYPE_SYNC) : "=r"(sync));
  if (!sync)
    return 1;
  *group = sync;
  return 0;
}

int thread_create_in_group(void *(*fptr)(void *), thread_group_t group,
                           void *stack, unsigned num_stack_words, void *args)
{
  unsigned t;
  asm volatile("getst %0, res[%1]" : "=r"(t) : "r"(group));
  if (!t)
    return 1;
  is_detached[t >> XS1_RES_ID_RESNUM_SHIFT] = 0;
  asm volatile("init t[%0]:pc, %1" : /* no outputs*/ : "r"(t), "r"(fptr));
  asm volatile("init t[%0]:sp, %1" : /* no outputs*/ : "r"(t), "r"((int *)stack + num_stack_words - 1));
  asm volatile("init t[%0]:lr, %1" : /* no outputs*/ : "r"(t), "r"(&joinable_thread_exit));
  asm volatile("set t[%0]:r0, %1" : /* no outputs*/ : "r"(t), "r"(args));
  return 0;
}

void thread_exit(void *value)
{
  if (is_detached[__builtin_getid()])
    detached_thread_exit();
  else
    joinable_thread_exit(value);
}

/* Force definitions of inline functions in this translation unit. */
extern inline void thread_group_start(thread_group_t group);
extern inline void thread_sync(void);
extern inline void thread_group_sync(thread_group_t group);
