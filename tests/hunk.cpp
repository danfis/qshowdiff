#include <cppu.h>
#include "../hunk.h"


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
}

void testIterators()
{
    Hunk hunk(100,120);

    hunk.addSnippet(new Context(new Text(text)));
    hunk.addSnippet(new Added(new Text(text2)));
    hunk.addSnippet(new Changed(new Text(text), new Text(text2)));

    Hunk::iterator it = hunk.begin();
    Hunk::iterator it_end = hunk.end();
    assertEquals((*it).original(), Context(new Text(text)).original());
    assertEquals((*it).modified(), Context(new Text(text)).modified());

    it++;
    it++;
    assertEquals((*it).original(), Changed(new Text(text), new Text(text2)).original());
    assertEquals((*it).modified(), Changed(new Text(text), new Text(text2)).modified());

    assertEquals(hunk.numSnippets(), 3);
}

TESTS{
    REG_TEST(testConstructors);
    REG_TEST(testIterators);
}
TEST_CASE_END;
