#ifndef TEST_LEVEN
#define TEST_LEVEN

#include "cu/cu.h"

TEST(levenshteinSetUp);
TEST(levenshteinTable);
TEST(levenshteinRanges);

TEST_SUITE(TSLevenshtein) {
    TEST_ADD(levenshteinSetUp),

    TEST_ADD(levenshteinTable),
    TEST_ADD(levenshteinRanges),

    TEST_SUITE_CLOSURE
};

#endif
