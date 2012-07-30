#include <xs1.h>

/** 
 * Function that produces a random number. The number has a cycle of 2^32
 * and is produced using a LFSR.
 */
int randomSimple();


/** 
 * Function that modifies the seed.
 *
 * \param x  value to be folded into the seed.
 */
void randomSimpleSeed(int x);

#define RANDOM_SIMPLE_INIT_SEED  __attribute__((constructor)) void random_simple_init_seed(){ setps(0x060b, 0x3); }

/** Function that attempts to fold a true random value into the seed, using
 * an asynchronous timer. If the random number generator should be seeded
 * from a true random basis, then this function should be called once in
 * main, and RANDOM_SIMPLE_INIT_SEED should be included in your code.
 */
void randomSimpleRandomiseSeed();
