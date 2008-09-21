#ifndef TEST_HUNK
#define TEST_HUNK

#include "cu/cu.h"

TEST(hunkSetUp);
TEST(hunkConstructors);

TEST_SUITE(TSHunk) {
    TEST_ADD(hunkSetUp),
    TEST_ADD(hunkConstructors),

    TEST_SUITE_CLOSURE
};

#endif
