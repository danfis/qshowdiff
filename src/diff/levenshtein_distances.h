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

#ifndef _LEVENSHTEIN_DISTANCES_H_
#define _LEVENSHTEIN_DISTANCES_H_

#include <utility>
#include <vector>
#include <list>

#include "levenshtein_table.h"
#include "text.h"


/**
 * Class which describes Levenshtein distances between two texts given in
 * constructor.
 */
class LevenshteinDistances{
  private:
    /**
     * Deletion ranges.
     * Each item of list represents one line which is built from list of
     * deletion ranges.
     */
    std::vector<std::vector<range_t> > _ranges_original;
    std::vector<std::vector<range_t> > _ranges_modified;

    /**
     * Iterators pointing to current deletion range which will be returned
     * by nextDeletionRangeOriginal/Modified.
     */
    std::vector<range_t>::iterator _current_it_original;
    std::vector<range_t>::iterator _current_it_modified;

    /**
     * Which line is currently managed.
     */
    int _current_line;

  public:
    /**
     * Constructor.
     * Must build the table, fill _ranges_original/modified
     * structures and set default values to _current_it_original/modified
     * and _current_line.
     */
    LevenshteinDistances(const Text &original, const Text &modified);

    /**
     * Number of lines of original and modified text.
     */
    int numLines() const { return _ranges_original.size(); }

    /**
     * Change current read line to line.
     */
    void setCurrentLine(int line)
        { if (line >= numLines()) return;
          _current_line = line;
          _current_it_original = _ranges_original[_current_line].begin();
          _current_it_modified = _ranges_modified[_current_line].begin();}

    /**
     * Store into r current range on which is pointing
     * internal iterator.
     * Returns true, if range was filled.
     * Returns false, if range could not be filled because there is no more
     * ranges.
     */
    bool nextRangeOriginal(range_t &r)
        { if (_current_it_original == _ranges_original[_current_line].end())
            return false;
          r = *(_current_it_original++); return true; }
    bool nextRangeModified(range_t &r)
        { if (_current_it_modified == _ranges_modified[_current_line].end())
            return false;
          r = *(_current_it_modified++); return true; }

    const list_of_ranges_t &getRangesOriginal() const
        { return const_cast<const list_of_ranges_t&>(_ranges_original); }
    const list_of_ranges_t &getRangesModified() const
        { return const_cast<const list_of_ranges_t&>(_ranges_modified); }

    /**
     * Reset table to initial values.
     */
    void reset() { _current_line = 0;
        _current_it_original = _ranges_original[0].begin();
        _current_it_modified = _ranges_modified[0].begin(); }
};
#endif
