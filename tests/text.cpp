#include <cppu.h>
#include <iostream>
using namespace std;

#include "text.h"

TEST_CASE(TestCaseText);

Text t;
void setUp()
{
	t.addLine(new QString("Line1"));
	t.addLine(new QString("Line2"));
	t.addLine(new QString("Line3"));
	t.addLine(new QString("Line4"));
}

void testAdd()
{
	Text t2;
	t2.addLine(new QString("Line1"));
	t2.addLine(new QString("Line2"));

	assertEquals(t2.numLines(), 2);
}

void testConstruct()
{
	Text t2(t);
	Text *t3 = new Text(t2);
	Text *t4 = new Text(*t3);
	delete t3;
	delete t4;
}

void testOperators()
{
	Text t2;
	t2 = t;
	assertTrue(t.numLines() == t2.numLines());
	assertTrue(t == t2);
	Text t3;
	assertTrue(t != t3);
}


TESTS{
	REG_TEST(testAdd);
	REG_TEST(testConstruct);
	REG_TEST(testOperators);
}
TEST_CASE_END;

