#include <stdio.h>
#include <random.h>

RANDOM_SIMPLE_INIT_SEED

int main(void) {
    randomSimpleSeed(12345);
    randomSimpleRandomiseSeed();
    printf("%08x\n", randomSimple());
    printf("%08x\n", randomSimple());
    printf("%08x\n", randomSimple());
}
