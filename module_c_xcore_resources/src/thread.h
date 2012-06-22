#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned thread_t;
typedef unsigned thread_group_t;

#ifndef __XC__

/**
 * thread_create() allocates and starts a new thread. The thread executes
 * \a start_routine with \a arg as its only argument. If \a start_routine
 * returns the effect is as if there was a call to thread_exit() using the
 * return value of \a start_routine as the exit value.
 *
 * The calling thread must call thread_join() to reclaim the resources used to
 * create the thread.
 *
 * \param t On successful creation of the thread the ID of the thread's
            synchronizer is stored to this argument.
 * \param start_routine The function to execute on the thread.
 * \param stack Pointer to a block of memory that is used for the new thread's stack.
 * \param num_stack_words Size of the \a stack argument in words.
 * \param args The argument to pass to \a start_routine.
 * \return 0 on success, non zero on failure.
 */
int thread_create(thread_t *t, void *(*start_routine)(void *), void *stack,
                  unsigned num_stack_words, void *arg);

/**
 * thread_create_detached() allocates and starts a new thread. The thread
 * executes \a start_routine with \a arg as its only argument. If
 * \a start_routine returns the effect is as if there was a call to
 * thread_exit() using the return value of \a start_routine as the exit value.
 *
 * Unlike thread_create() the resources used to create the thread as reclaimed
 * as soon as the thread terminates.
 *
 * \param start_routine The function to execute on the thread.
 * \param stack Pointer to a block of memory that is used for the new thread's stack.
 * \param num_stack_words Size of the \a stack argument in words.
 * \param args The argument to pass to \a start_routine.
 * \return 0 on success, non zero on failure.
 */
int thread_create_detached(void *(*start_routine)(void *), void *stack,
                           unsigned stackspace, void *arg);

/**
 * thread_join() pauses execution of the calling thread until the thread
 * specified as an argument terminates. The behaviour is undefined if
 * thread_join() is called multiple times with the same thread.
 *
 * \param thread The synchronizer of the thread to wait for.
 * \return The exit value passed to thread_exit() by the terminating thread.
 */
void *thread_join(thread_t thread);

/**
 * thread_exit() terminates execution of the calling thread. If the thread was
 * created using thread_create() the exit value is made available to a thread
 * calling thread_join().
 *
 * The behaviour is undefined is thread_exit() is called from a thread which was
 * not started by thread_create(), thread_create_detached() or
 * thread_create_in_group().
 */
void thread_exit(void *value) __attribute__((noreturn));

/**
 * thread_group_create() allocates a new thread group. Thread groups support
 * efficient barrier synchronization via the thread_sync() and
 * thread_group_sync() functions.
 * Threads are added to the thread group using thread_create_in_group().
 * Threads in the thread group are initially paused. thread_group_start() is
 * used to start execution of all threads in the thread group.
 * thread_group_join() must be called to reclaim the resources used to create
 * the thread group.
 *
 * \param t On successful creation of the thread group the ID of the thread
            group's synchronizer is stored to this argument.
 * \return 0 on success, non zero on failure.
 */
int thread_group_create(thread_group_t *group);

/**
 * thread_create_in_group() allocates a new thread and adds it to the specified
 * thread group. The thread group must not have already been started.
 * The allocated thread is initially paused. When the thread group is started
 * the allocated thread will call \a start_routine with \a arg as its only
 * argument. If \a start_routine returns the effect is as if there was a call
 * to thread_exit() using the return value of \a start_routine as the exit
 * value.
 *
 * \param start_routine The function to execute on the thread.
 * \param group The thread group for the thread.
 * \param stack Pointer to a block of memory that is used for the new thread's
                stack.
 * \param num_stack_words Size of the \a stack argument in words.
 * \param args The argument to pass to \a start_routine.
 * \return 0 on success, non zero on failure.
 */
int thread_create_in_group(void *(*start_routine)(void *), thread_group_t group,
                           void *stack, unsigned num_stack_words, void *arg);

/**
 * thread_group_start() starts all threads in the thread group.
 */
inline void thread_group_start(thread_group_t group) {
  asm volatile("msync res[%0]" : /* no outputs*/ : "r"(group) : "memory");
}

/**
 * thread_sync() pauses execution of the current thread utill all threads in the
 * same thread group have called thread_sync() and thread_group_sync() has been
 * called in the parent thread.
 */
inline void thread_sync(void) {
  asm volatile("ssync" : /* no outputs */ : /* no inputs */ : "memory");
}

/**
 * thread_group_sync() pauses execution of the current thread utill all threads
 * in the thread group have called thread_sync(). An exception will be raised if
 * any threads in the thread group have exited.
 */
inline void thread_group_sync(thread_group_t group)  {
  asm volatile("msync res[%0]" : /* no outputs*/ : "r"(group) : "memory");
}

/**
 * Pauses execution of the current thread until all threads in the thread group
 * have exited.
 */
void thread_group_join(thread_group_t group);

#endif __XC__

#endif // THREAD_H_
