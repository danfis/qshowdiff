#include <cppu.h>
#include "hunk.h"


TEST_CASE(TestCaseHunk);
Text text;
Text text2;
void setUp()
{
    text.addLine(new QString("Line1"));
    text.addLine(new QString("Line2"));
    text.addLine(new QString("Line3"));
    text.addLine(new QString("Line4"));
    text.addLine(new QString("Line5"));

    text2.addLine(new QString("L1"));
    text2.addLine(new QString("L2"));
    text2.addLine(new QString("L3"));
    text2.addLine(new QString("L4"));
    text2.addLine(new QString("L5"));
}

void testConstructors()
{
    Hunk hunk(100,200);
    Hunk hunk2(hunk);
    Hunk hunk3(200,100);
    hunk3 = hunk;

    assertEquals(hunk.originalBeginsAt(), hunk2.originalBeginsAt());
    assertEquals(hunk.modifiedBeginsAt(), hunk3.modifiedBeginsAt());
    assertEquals(hunk.originalBeginsAt(), hunk3.originalBeginsAt());

    assertEquals(hunk, hunk2);
    assertEquals(hunk, hunk3);
    Hunk hunk4(105, 100);
    assertNotEquals(hunk, hunk4);
}

TESTS{
    REG_TEST(testConstructors);
}
TEST_CASE_END;
