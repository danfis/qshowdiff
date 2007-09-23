#include <cppu.h>
#include "diff.h"


TEST_CASE(TestCaseDiff);
void testSingelton()
{
    Diff *diff1 = Diff::instance();
    Diff *diff2 = Diff::instance();
    assertEquals(diff1, diff2);
}

TESTS{
    REG_TEST(testSingelton);
}
TEST_CASE_END;

