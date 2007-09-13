#include <cppu.h>
#include <iostream>
using namespace std;

#include "../text.h"

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

void testIterator()
{
	QString comp1;
	QString comp2;
	comp1.append("Line1");
	comp1.append("Line2");
	comp1.append("Line3");
	comp1.append("Line4");
	
	Text::iterator it = t.begin();
	Text::iterator it_end = t.end();

	for (;it != it_end; it++){
		comp2.append(*it);
	}
	assertTrue(comp1 == comp2);

	it = t.begin();
	assertTrue(it++ == ++it);
	it++;
	assertTrue(it-- == --it);
	it_end = it;
	assertTrue(it == it_end);

    it = t.begin();
    Text::iterator it2(it);
    assertTrue(it2 == it);
}

TESTS{
	REG_TEST(testAdd);
	REG_TEST(testConstruct);
	REG_TEST(testOperators);
	REG_TEST(testIterator);
}
TEST_CASE_END;

