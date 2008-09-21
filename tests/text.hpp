#ifndef TEST_TEXT
#define TEST_TEXT

#include "cu/cu.h"

TEST(textSetUp);
TEST(textAdd);
TEST(textConstruct);
TEST(textOperators);

TEST_SUITE(TSText) {
    TEST_ADD(textSetUp),

    TEST_ADD(textAdd),
    TEST_ADD(textConstruct),
    TEST_ADD(textOperators),

    TEST_SUITE_CLOSURE
};

#endif
