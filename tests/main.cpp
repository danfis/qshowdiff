#include "text.cpp"
#include "hunk.cpp"
#include "diff.cpp"
#include "levenshtein.cpp"

TEST_SUITE(TestSuiteAll);
    REG(TestCaseText);
    REG(TestCaseHunk);
    REG(TestCaseDiff);
    REG(TestCaseLevenshtein);
TEST_SUITE_END;

int main(int argc, char *argv[])
{
	RUN(TestSuiteAll);
}

