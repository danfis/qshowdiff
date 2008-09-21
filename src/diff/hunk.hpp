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

#ifndef _HUNK_H_
#define _HUNK_H_

#include <vector>

#include "diff/snippet.hpp"
#include "diff/utils.hpp"


/**
 * This class describes a hunk of changes from diff.
 * Hunk is aggregation of snippets.
 */
class Hunk : public VectorOfPointers<Snippet>{
  private:
    int _original_from_line;//! line on which begin changes in original file
    int _modified_from_line;//! line on which begin changes in modified file

    void _copy(const Hunk &h)
        { _original_from_line = h._original_from_line;
          _modified_from_line = h._modified_from_line; }

  public:
    Hunk(const int original_from, const int modified_from) :
        VectorOfPointers<Snippet>(),
        _original_from_line(original_from),
        _modified_from_line(modified_from){}
    Hunk(const Hunk &h) : VectorOfPointers<Snippet>(h) { _copy(h); }
    ~Hunk(){}

    Hunk &operator=(const Hunk &h)
        { VectorOfPointers<Snippet>::operator=(h); _copy(h); return *this; }

    bool operator==(const Hunk &h) const
        { return _original_from_line == h._original_from_line &&
                 _modified_from_line == h._modified_from_line &&
                 VectorOfPointers<Snippet>::operator==(h);}
    bool operator!=(const Hunk &h) const { return !(*this == h);}

    void addSnippet(Snippet *sn){ VectorOfPointers<Snippet>::_add(sn); }
    int numSnippets() const { return VectorOfPointers<Snippet>::_size(); }

    int originalBeginsAt() const { return _original_from_line;}
    int modifiedBeginsAt() const { return _modified_from_line;}
};
#endif
