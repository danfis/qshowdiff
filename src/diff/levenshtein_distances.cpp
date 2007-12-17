/**
 * QShowDiff
 * ----------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of QShowDiff
 *
 * QShowDiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QShowDiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QShowDiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "levenshtein_distances.h"
#include "../debug.h"
using std::vector;
using std::pair;
using std::list;


/* LevenshteinDistances */
LevenshteinDistances::LevenshteinDistances(const Text &original, const Text &modified)
{
    int orig_len = original.numLines();
    int modif_len = modified.numLines();
    int len = std::min(orig_len, modif_len);
    int i;
    LevenshteinTable *table;
    range_t range;
    vector<range_t> ranges;
    vector<range_t>::const_iterator it;
    vector<range_t>::const_iterator it_end;
 
    _ranges_original.resize(std::max(orig_len, modif_len));
    _ranges_modified.resize(std::max(orig_len, modif_len));
    for (i=0; i < len; i++){
        ranges.clear();

        table = new LevenshteinTable(original.getLine(i), modified.getLine(i));

        table->fillRanges(ranges);
        it = ranges.begin();
        it_end = ranges.end();
        for (;it != it_end; it++){
            if ((*it).original){
                _ranges_original[i].push_back(*it);
            }else{
                _ranges_modified[i].push_back(*it);
            }
        }

        delete table;
    }
    for (;i < orig_len; i++){
        range.type = range_t::INSERTION;
        range.original = true;
        range.from = 0;
        range.length = original.getLine(i).size();

        _ranges_original[i].push_back(range);
    }
    for (;i < modif_len; i++){
        range.type = range_t::INSERTION;
        range.original = false;
        range.from = 0;
        range.length = modified.getLine(i).size();

        _ranges_modified[i].push_back(range);
    }
}
/* LevenshteinDistances END */
