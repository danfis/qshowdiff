#ifndef TEST_DIFF
#define TEST_DIFF

#include "cu/cu.h"

TEST(diffSingleton);

TEST_SUITE(TSDiff) {
    TEST_ADD(diffSingleton),
    TEST_SUITE_CLOSURE
};

#endif
