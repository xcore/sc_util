#ifndef C_ATHREAD_H

#define C_ATHREAD_H
/** Type that denotes an asynchronous thread. Variables of this type should
 * be initalised using athread_init(). Running asynchronous threads should
 * terminate themselves using athread_exit().
 */
typedef unsigned int athread_t;

/** Macro that allocates and starts an asynchronous thread. The thread has
 * to be provided with a stack and a function to execute. When the thread
 * is finished, the thread should call athread_exit(). If a function is
 * passed as the ``pc`` argument, then this function should never return,
 * but instead call athread_exit().
 *
 * \param t     thread to be created.
 *
 * \param stack pointer to a block of memory where the thread's stack can
 *              be created.
 * 
 * \param num_stack_words size of the block of memory reserved for the
 *              stack in words.
 *
 * \param pc    code to execute (a void function)
 */
void athread_init(athread_t t, unsigned int *stack, unsigned num_stack_words, void (*pc)());

#define athread_init(t, stack, num_stack_words, pc)    \
    asm volatile("getr %0,4" : "=r" (t)); \
    asm volatile("init t[%0]:sp,%1" :: "r" (t), "r" (&stack[num_stack_words-1])); \
    asm volatile("init t[%0]:pc,%1" :: "r" (t), "r" (pc)); \
    asm volatile("start t[%0]" :: "r" (t));

/** Macro that exits an asynchronous thread. Statements after this macro
 * are unreachable, since it terminates the running thread.
 */
void athread_exit(void);
/** \cond */
#define athread_exit()       asm volatile("freet");
/** \endcond */

#endif
