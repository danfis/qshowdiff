#include "cu/cu.h"
#include "diff/diff.hpp"


TEST(diffSingleton)
{
    Diff *diff1 = Diff::instance();
    Diff *diff2 = Diff::instance();
    assertEquals(diff1, diff2);
}
