#include "text.cpp"
#include "snippet.cpp"
#include "hunk.cpp"

TEST_SUITE(TestSuiteAll);
    REG(TestCaseText);
    REG(TestCaseSnippet);
    REG(TestCaseHunk);
TEST_SUITE_END;

int main(int argc, char *argv[])
{
	RUN(TestSuiteAll);
}

