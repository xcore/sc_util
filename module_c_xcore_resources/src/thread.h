#ifndef C_THREAD_H

#define C_THREAD_H
/** Type that denotes a thread. Variables of this type should be initalised
 * using thread_init(). Running threads should terminate themselves using
 * thread_exit().
 */
typedef unsigned int thread_t;

/** Macro that allocates and starts an asynchronous thread. The thread has
 * to be provided with a stack and a function to execute. When the thread
 * is finished, the thread should call thread_exit(). If a function is
 * passed as the ``pc`` argument, then this function should never return,
 * but instead call thread_exit().
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
void thread_init(thread_t t, unsigned int *stack, unsigned num_stack_words, void (*pc)());

#define thread_init(t, stack, num_stack_words, pc)    \
    asm volatile("getr %0,4" : "=r" (t)); \
    asm volatile("init t[%0]:sp,%1" :: "r" (t), "r" (&stack[num_stack_words-1])); \
    asm volatile("init t[%0]:pc,%1" :: "r" (t), "r" (pc)); \
    asm volatile("start t[%0]" :: "r" (t));

/** Macro that exits a thread. Statements after this macro are unreachable,
 * since it terminates the running thread.
 */
void thread_exit(void);
/** \cond */
#define thread_exit()       asm volatile("freet");
/** \endcond */

#endif
