#include "cu/cu.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include "diff/text.hpp"
#include "diff/levenshtein_table.hpp"
#include "diff/levenshtein_distances.hpp"

/*
static void printTable(vector<vector<int> > &table)
{
    int rows = table.size();
    int cols = table[0].size();

    for (int i=0; i < rows; i++){
        for (int j=0; j < cols; j++){
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}
static void printTrace(list<pair<int, int> > &trace)
{
    list<pair<int, int> >::const_iterator it = trace.begin();
    list<pair<int, int> >::const_iterator it_end = trace.end();
    for (; it != it_end; it++){
        cout << "(" << (*it).first << ", " << (*it).second << ") ";
    }
    cout << endl;
}
*/

static void printRanges(vector<range_t> &ranges)
{
    int len = ranges.size();
    cout << "INSERTION: " << range_t::INSERTION << endl;
    cout << "SUBSTITUTION: " << range_t::SUBSTITUTION << endl;
    for (int i=0; i < len; i++){
        cout << "type: " << ranges[i].type << ", "
             << "original: " << ranges[i].original << ", "
             << "from: " << ranges[i].from << ", "
             << "length: " << ranges[i].length << endl;
    }
}

static vector<vector<int> > table;
static list<pair<int, int> > trace;
static vector<range_t> ranges;
static QString original;
static QString modified;

TEST(levenshteinSetUp)
{
    original = "kitten";
    modified = "sitting";

    table.resize(8);
    for (int i=0; i < 8; i++){
        table[i].resize(7);
        table[i][0] = i;
    }
    for (int i=0; i < 7; i++)
        table[0][i] = i;

    table[1][1] = 1; table[1][2] = 2; table[1][3] = 3;
    table[1][4] = 4; table[1][5] = 5; table[1][6] = 6;

    table[2][1] = 2; table[2][2] = 1; table[2][3] = 2;
    table[2][4] = 3; table[2][5] = 4; table[2][6] = 5;

    table[3][1] = 3; table[3][2] = 2; table[3][3] = 1;
    table[3][4] = 2; table[3][5] = 3; table[3][6] = 4;

    table[4][1] = 4; table[4][2] = 3; table[4][3] = 2;
    table[4][4] = 1; table[4][5] = 2; table[4][6] = 3;

    table[5][1] = 5; table[5][2] = 4; table[5][3] = 3;
    table[5][4] = 2; table[5][5] = 2; table[5][6] = 3;

    table[6][1] = 6; table[6][2] = 5; table[6][3] = 4;
    table[6][4] = 3; table[6][5] = 3; table[6][6] = 2;

    table[7][1] = 7; table[7][2] = 6; table[7][3] = 5;
    table[7][4] = 4; table[7][5] = 4; table[7][6] = 3;

    trace.push_front(pair<int, int>(7, 6));
    trace.push_front(pair<int, int>(6, 6));
    trace.push_front(pair<int, int>(5, 5));
    trace.push_front(pair<int, int>(4, 4));
    trace.push_front(pair<int, int>(3, 3));
    trace.push_front(pair<int, int>(2, 2));
    trace.push_front(pair<int, int>(1, 1));

    range_t range;
    
    range.type = range_t::SUBSTITUTION;
    range.original = true;
    range.from = 0;
    range.length = 1;
    ranges.push_back(range);

    range.original = false;
    ranges.push_back(range);

    range.original = true;
    range.from = 4;
    range.length = 1;
    ranges.push_back(range);

    range.original = false;
    ranges.push_back(range);

    range.type = range_t::INSERTION;
    range.original = false;
    range.from = 6;
    range.length = 1;
    ranges.push_back(range);
}

TEST(levenshteinTable)
{
    LevenshteinTable l_table(original, modified);
    vector<vector<int> > table2;
    list<pair<int, int> > trace2;
    l_table.dumpTable(table2);
    l_table.dumpTrace(trace2);

    assertEqualsM(table, table2, "Incorrect Levenshtein table.");
    assertEqualsM(trace, trace2, "Incorrect trace back.");
}

TEST(levenshteinRanges)
{
    LevenshteinTable l_table(original, modified);
    vector<range_t> ranges2;
    l_table.fillRanges(ranges2);

    printRanges(ranges);
    printRanges(ranges2);

    assertEqualsM(ranges.size(), ranges2.size(), "Incorrect size of ranges.");
    int len = ranges.size();
    for (int i=0; i < len; i++){
        assertTrue(ranges2.end() != std::find(ranges2.begin(), ranges2.end(),
                                              ranges[i]));
    }
}
