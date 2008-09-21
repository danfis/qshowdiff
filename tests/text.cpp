#include "cu/cu.h"
#include <iostream>
using namespace std;

#include "diff/text.hpp"

static Text t;
TEST(textSetUp)
{
	t.addLine(new QString("Line1"));
	t.addLine(new QString("Line2"));
	t.addLine(new QString("Line3"));
	t.addLine(new QString("Line4"));
}

TEST(textAdd)
{
	Text t2;
	t2.addLine(new QString("Line1"));
	t2.addLine(new QString("Line2"));

	assertEquals(t2.numLines(), 2);
}

TEST(textConstruct)
{
	Text t2(t);
	Text *t3 = new Text(t2);
	Text *t4 = new Text(*t3);
	delete t3;
	delete t4;
}

TEST(textOperators)
{
	Text t2;
	t2 = t;
	assertTrue(t.numLines() == t2.numLines());
	assertTrue(t == t2);
	Text t3;
	assertTrue(t != t3);
}
