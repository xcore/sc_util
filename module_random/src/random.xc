#include "random.h"

static unsigned int seed = -1;

int randomSimple() {
    crc32(seed, -1, 0xEDB88320);
    return seed;
}

void randomSimpleSeed(int x) {
    crc32(seed, x, 0xEDB88320);
}

void randomSimpleRandomiseSeed() {
    crc32(seed, getps(0x070B), 0xEDB88320);
}
