#ifndef C_STHREAD_H

#define C_STHREAD_H
/** Type that denotes a synchronous thread. Variables of this type should
 * be initalised using sthread_init(). Running synchronous threads should
 * terminate themselves using sthread_exit().
 */
typedef unsigned int sthread_t;

/** Type that denotes a synchroniser that is used for a group of threads.
 * Variables of this type should be initalised using sthread_init_sync()
 * and be deinitialised using sthread_sync_exit().
 */
typedef unsigned int sthread_sync_t;

/** Macro that allocates a synchroniser, which is needed to make a group of
 * synchronous threads. This synchroniser is deallocated upon calling but
 * instead call sthread_join().
 *
 * \param s synchroniser to be created.
 */
void sthread_sync_init(sthread_sync_t s);
#define sthread_sync_init(s) \
    asm volatile("getr %0,3" : "=r" (s));

/** Macro that allocates a synchronous thread. The thread has
 * to be provided with a stack and a function to execute. When the thread
 * is finished, the thread should call sthread_exit(). If a function is
 * passed as the ``pc`` argument, then this function should never return,
 * but instead call sthread_exit().
 *
 * Note that all threads belnging to a synchroniser shoudl be created
 * first, prior to starting them using sthread_start().
 *
 * \param t     thread to be created.
 *
 * \param s synchroniser that this thread belongs to.
 *
 * \param stack pointer to a block of memory where the thread's stack can
 *              be created.
 * 
 * \param num_stack_words size of the block of memory reserved for the
 *              stack in words.
 *
 * \param pc    code to execute (a void function)
 */
void sthread_init(sthread_t t, sthread_sync_t s, unsigned int *stack, unsigned num_stack_words, void (*pc)());

#define sthread_init(t, s, stack, num_stack_words, pc)                   \
    asm volatile("getst %0,res[%1]" : "=r" (t) : "r" (s));              \
    asm volatile("init t[%0]:sp,%1" :: "r" (t), "r" (&stack[num_stack_words-1])); \
    asm volatile("init t[%0]:pc,%1" :: "r" (t), "r" (pc));

/** Macro that starts a group of synchronous threads.
 *
 * \param s syncrhoniser whose threads should start.
 */
void sthread_start(sthread_sync_t s);

#define sthread_start(s)    \
    asm volatile("msync res[%0]" :: "r" (s));

/** Macro that joins a group of synchronous threads. This frees the
 * synchroniser and all threads.
 *
 * \param s syncrhoniser whose threads should join.
 */
void sthread_join(sthread_sync_t s);

#define sthread_join(s)    \
    asm volatile("mjoin res[%0]" :: "r" (s)); \
    asm volatile("freer res[%0]" :: "r" (s));

/** Macro that exits a synchronous thread. Statements after this macro
 * are unreachable, since it terminates the running thread.
 */
void sthread_exit(void);
/** \cond */
#define sthread_exit()       asm volatile("ssync");
/** \endcond */

#endif
