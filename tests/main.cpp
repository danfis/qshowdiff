#include "text.cpp"
#include "snippet.cpp"
#include "hunk.cpp"
#include "diff.cpp"
#include "levenshtein.cpp"

TEST_SUITE(TestSuiteAll);
    REG(TestCaseText);
    REG(TestCaseSnippet);
    REG(TestCaseHunk);
    REG(TestCaseDiff);
    REG(TestCaseLevenshtein);
TEST_SUITE_END;

int main(int argc, char *argv[])
{
	RUN(TestSuiteAll);
}

