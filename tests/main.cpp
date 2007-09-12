#include "text.cpp"
#include "snippet.cpp"

TEST_SUITE(TestSuiteAll);
    REG(TestCaseText);
    REG(TestCaseSnippet);
TEST_SUITE_END;

int main(int argc, char *argv[])
{
	RUN(TestSuiteAll);
}

