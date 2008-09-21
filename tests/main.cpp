#include "cu/cu.h"

#include "diff.hpp"
#include "hunk.hpp"
#include "levenshtein.hpp"
#include "text.hpp"

TEST_SUITES{
    TEST_SUITE_ADD(TSDiff),
    TEST_SUITE_ADD(TSHunk),
    TEST_SUITE_ADD(TSLevenshtein),
    TEST_SUITE_ADD(TSText),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_OUT_PREFIX("regressions/");
    CU_RUN(argc, argv);

    return 0;
}
