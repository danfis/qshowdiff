#include "levenshtein_table.h"
#include "../debug.h"
using std::vector;
using std::pair;
using std::list;

/* LevenshteinTable */
LevenshteinTable::LevenshteinTable(const QString &orig, const QString &modif)
    : _original(orig), _modified(modif)
{
    _allocateMemory();
    _fillTable();
    _findTrace();
}

void LevenshteinTable::fillRanges(std::vector<range_t> &ranges) const
{
    int row = 0;
    int col = 0;
    pair<int, int> from(0,0);
    range_t::range_type current_type = range_t::NOCHANGE;
    list<pair<int, int> >::const_iterator it = _trace.begin();
    list<pair<int, int> >::const_iterator it_end = _trace.end();

    do{
        // substitution / nochange
        if ((*it).first-1 == row && (*it).second-1 == col){
            DBG("Substitution");
            if (_table[row][col] != _table[(*it).first][(*it).second]){
                if (current_type != range_t::SUBSTITUTION){
                    _finishRange(ranges, current_type, from, *it);
                    from = (*it);
                }
                current_type = range_t::SUBSTITUTION;
            }else{
                _finishRange(ranges, current_type, from, *it);
                current_type = range_t::NOCHANGE;
            }
        }else
        // insertion to modified
        if ((*it).first-1 == row){
            DBG("Insertion");
            if (current_type != range_t::INSERTION){
                _finishRange(ranges, current_type, from, *it);
                from = *it;
            }
            current_type = range_t::INSERTION;
        }else
        // insertion to original / deletion in modified
        if ((*it).second-1 == col){
            DBG("Deletion");
            if (current_type != range_t::DELETION){
                _finishRange(ranges, current_type, from, *it);
                from = *it;
            }
            current_type = range_t::DELETION;
        }

        row = (*it).first;
        col = (*it).second;

        it++;
    }while (it != it_end);

    _finishRange(ranges, current_type, from, pair<int,int>(_table.size(),
                _table[0].size()));
}


void LevenshteinTable::dumpTable(vector<vector<int> > &dump) const
{
    int rows = _table.size();

    dump.resize(rows);
    for (int i=0; i < rows; i++){
        dump[i] = _table[i];
    }
}
void LevenshteinTable::dumpTrace(list<pair<int, int> > &dump) const
{
    list<pair<int, int> >::const_iterator it = _trace.begin();
    list<pair<int, int> >::const_iterator it_end = _trace.end();
    for (; it != it_end; it++){
        dump.push_back(*it);
    }
}



// private:
void LevenshteinTable::_allocateMemory()
{
    int orig_len = _original.size();
    int modif_len = _modified.size();

    _table.resize(modif_len + 1);
    for (int i=0; i < modif_len + 1; i++){
        _table[i].resize(orig_len + 1);
    }
}

void LevenshteinTable::_fillTable()
{
    int rows = _table.size();
    int cols = _table[0].size();
    int cost;

    for (int i=0; i < rows; i++)
        _table[i][0] = i;
    for (int i=0; i < cols; i++)
        _table[0][i] = i;

    for (int i=1; i < rows; i++){
        for (int j=1; j < cols; j++){
            cost = _original[j - 1] == _modified[i - 1] ? 0 : 1;
            _table[i][j] = _min(_table[i - 1][j] + 1,
                                _table[i][j - 1] + 1,
                                _table[i - 1][j - 1] + cost);
        }
    }
}

void LevenshteinTable::_findTrace()
{
    int row = _table.size() - 1;
    int column = _table[0].size() - 1;
    pair<int, int> tmp;

    do {
        _trace.push_front(pair<int, int>(row, column));
        _minAncestor(row, column);
    }while(row != 0 && column != 0);
}

void LevenshteinTable::_minAncestor(int &row, int &column) const
{
    if (row == 0 && column == 0){
        return;
    }else if (row == 0){
        column = column - 1;
        return;
    }else if (column == 0){
        row = row - 1;
        return;
    }

    int up = _table[row - 1][column];
    int left = _table[row][column - 1];
    int askan = _table[row - 1][column - 1];
    int min = _min(up, left, askan);

    if (min == askan){
        row = row - 1;
        column = column - 1;
    }else if (min == up){
        row = row - 1;
        column = column;
    }else if (min == left){
        row = row;
        column = column - 1;
    }
}

void LevenshteinTable::_finishRange(vector<range_t> &ranges,
        range_t::range_type type,
        const pair<int, int> &from, const pair<int, int> &to) const
{
    range_t range;

    if (type == range_t::NOCHANGE)
        return;

    if (type == range_t::INSERTION){
        range.original = false;
        range.type = range_t::INSERTION;
        range.from = from.first - 1;
        range.length = to.first - 1 - range.from;

        ranges.push_back(range);
    }else if (type == range_t::DELETION){
        range.original = true;
        range.type = range_t::INSERTION;
        range.from = from.second - 1;
        range.length = to.second - 1 - range.from;

        ranges.push_back(range);
    }else if (type == range_t::SUBSTITUTION){
        range.original = true;
        range.type = range_t::SUBSTITUTION;
        range.from = from.second - 1;
        range.length = to.second - 1 - range.from;
        ranges.push_back(range);

        range.original = false;
        range.type = range_t::SUBSTITUTION;
        range.from = from.first - 1;
        range.length = to.first - 1 - range.from;
        ranges.push_back(range);
    }
}

int LevenshteinTable::_min(int a, int b) const
{
    return a < b ? a : b;
}
int LevenshteinTable::_min(int a, int b, int c) const
{
    int m = a < b ? a : b;
    return m < c ? m : c;
}
/* LevenshteinTable END */



