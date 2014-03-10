/*
 * Copyright (C) XMOS Limited 2008
 *
 * The copyrights, all other intellectual and industrial property rights are
 * retained by XMOS and/or its licensors.
 *
 * The code is provided "AS IS" without a warranty of any kind. XMOS and its
 * licensors disclaim all other warranties, express or implied, including any
 * implied warranty of merchantability/satisfactory quality, fitness for a
 * particular purpose, or non-infringement except to the extent that these
 * disclaimers are held to be legally invalid under applicable law.
 *
 * Version: <version>
 */

#ifndef  __xfifo_h_
#define  __xfifo_h_
#include <xccompat.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
   \file xfifo.h
   \brief A cross-thread single core fifo queue library

   This library provides the ability to have a fifo between two threads.
   Fifo queues are data that can be shared between two threads, with one thread
   pushing into the queue and one thread pulling out.

   There are several restrictions to the use of this library:

   \li Only one thread can push and only one thread can pull
   \li A queue cannot be referenced across cores
   \li A queue must be initialized with fifo_init before use

 */

/** The overhead of fifo book-keeping information.
 *  When initializing a fifo the supplied buffer must have size
 *  at least the required length of the fifo plus this overhead
 */
#define FIFO_OVERHEAD 5

/** The type of a fifo queue.
 */
typedef unsigned int xfifo_t;

/** Initialize a fifo.
 *
 *  \param buf The fifo buffer to initialize. This must have size
 *              at least the required length of the fifo plus FIFO_OVERHEAD
 *  \param n The number of elements in the queue
 *  \return  A reference to the fifo
 *
 *  This function takes a reference to the buffer array.
 *  So you should not manipulate the buffer directly after the call to this
 *  function.
 */
extern xfifo_t xfifo_init(unsigned int q[], unsigned int n);

/** Return the number of elements in a queue
 *  \param q The queue to intialize
 *  \return The number of elements in the queue
 */
extern unsigned int xfifo_num_elements(xfifo_t q);

/** Query whether a queue contains no elements
 *
 *  \param q The queue to check
 *  \return non-zero if the queue if empty, zero otherwise
 */
extern unsigned int xfifo_is_empty(xfifo_t q);

/** Return non-zero if a queue is full
 *  \param q The queue to check
 *  \return non-zero if the queue if full, zero otherwise
 */
extern unsigned int xfifo_is_full(xfifo_t q);

/** Push an element into a queue.
 *  \param q The queue to push into
 *  \param x The item to push
 *  \return non-zero on success and 0 if queue was full.
 *
 *  If the queue is full then x is discarded.
 *
 */
extern unsigned int xfifo_push(xfifo_t q, unsigned int x);

/** Pull and element out of the a queue.
 *
 *  \param q The queue to pull out of
 *  \retval success  Set to non-zero if successful and 0
 *                   if the queue q was empty
 *  \returns The earliest added element still in the queue.
 *           If the queue is empty then the result is undefined.
 *
 */

extern unsigned int xfifo_pull(xfifo_t q,
                               REFERENCE_PARAM(unsigned int, success));

/** Push an element into a queue, blocking until the queue is not full.
 *  \param q The queue to push into
 *  \param x The item to push into the queue
 *  If the queue is full then busy wait
 *  until it is not full before pushing.
 */
extern void xfifo_blocking_push(xfifo_t q, unsigned int x);

/** Pull and element out of a queue, blocking until queue is non-empty.
 *  \param q The queue to pull out of
 *  \returns The earliest pushed in value still in the queue
 *
 *  If the queue is empty then busy wait until it s not empty before pulling.
 */
unsigned int xfifo_blocking_pull(xfifo_t q);


/** Push an element into a queue.
 *  \param q The queue to push into
 *  \param x The item to push
 *  \return non-zero on success and 0 if queue was full.
 *
 *  If the queue is full then x is discarded.
 *
 */
extern unsigned int xfifo_push(xfifo_t q, unsigned int x);



#ifdef __cplusplus
} //extern "C"
#endif

#endif // __xfifo_h_
