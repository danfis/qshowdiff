#include <cppu.h>
#include <QString>
#include "snippet.h"


TEST_CASE(TestCaseSnippet);
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
    Context context(new Text(text));
    Context context2(context);
    assertEquals(context.original(), context.modified());
    assertEquals(context.original(), context2.original());

    Added added(new Text(text));
    Added added2(added);
    assertEquals(added.original().numLines(), 0);
    assertEquals(added.modified(), added2.modified());

    Deleted deleted(new Text(text));
    Deleted deleted2(deleted);
    assertEquals(deleted.modified().numLines(), 0);
    assertEquals(deleted.original(), deleted2.original());

    Changed changed(new Text(text), new Text(text2));
    Changed changed2(changed);
    assertEquals(changed.original(), changed2.original());
    assertEquals(changed.modified(), changed2.modified());
}

void testOperators()
{
    Context context(new Text(text));
    Context context2 = context;
    assertEquals(context.original(), context2.original());
    assertEquals(context.modified(), context2.modified());
    assertEquals(context, context2);

    Added added(new Text(text));
    Added added2 = added;
    assertEquals(added.original(), added2.original());
    assertEquals(added.modified(), added2.modified());
    assertEquals(added, context);
}

TESTS{
    REG_TEST(testConstructors);
    REG_TEST(testOperators);
}

TEST_CASE_END;


