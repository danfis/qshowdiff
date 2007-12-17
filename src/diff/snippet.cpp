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

#include "snippet.h"
#include "../debug.h"

Snippet::Snippet(const Text &text)
{
    // no levenshtein
    _fromTextToTextSnippets(text, _original);
    //_modified is empty
}

Snippet::Snippet(const Text &original, const Text &modified)
{
    if (original.numLines() != modified.numLines()){
        _fromTextToTextSnippets(original, _original);
        _fromTextToTextSnippets(modified, _modified);
    }else{
        LevenshteinDistances leven(original, modified);
        const list_of_ranges_t orig_ranges = leven.getRangesOriginal();
        const list_of_ranges_t modif_ranges = leven.getRangesModified();
        int len = original.numLines();

        _original.resize(len);
        _modified.resize(len);

        for (int i=0; i < len; i++){
            //original:
            if (orig_ranges[i].size() == 0){
                _original[i].push_back(new TextSnippet(original.getLine(i),
                                                       range_t::NOCHANGE));
            }else{
                _splitByRanges(original.getLine(i), orig_ranges[i],
                        _original[i]);
            }

            //modified:
            if (modif_ranges[i].size() == 0){
                _modified[i].push_back(new TextSnippet(modified.getLine(i),
                                                       range_t::NOCHANGE));
            }else{
                _splitByRanges(modified.getLine(i), modif_ranges[i],
                        _modified[i]);
            }
        }
    }
}

void Snippet::_splitByRanges(const QString &str, const std::vector<range_t> &ranges,
                             TextSnippets &ts)
{
    int last = 0;
    int len = ranges.size();
    range_t range;

    for (int i=0; i < len; i++){
        range = ranges[i];

        if (range.from != last){
            ts.push_back(new TextSnippet(str.mid(last, range.from - last),
                                         range_t::NOCHANGE));
        }

        ts.push_back(new TextSnippet(str.mid(range.from, range.length),
                                     range.type));
        last = range.from + range.length;
    }

    if (last < str.size()){
        ts.push_back(new TextSnippet(str.mid(last), range_t::NOCHANGE));
    }
}

void Snippet::_fromTextToTextSnippets(const Text &text, ListOfTextSnippets &ts)
{
    int len = text.numLines();
    ts.resize(len);
    for (int i=0; i < len; i++){
        ts[i].push_back(new TextSnippet(text.getLine(i), range_t::NOCHANGE));
    }
}



void Snippet::_copy(const Snippet &s)
{
    int len, len2;

    len = s._original.size();
    _original.resize(len);
    for (int i=0; i < len; i++){
        len2 = s._original[i].size();
        for (int j=0; j < len2; j++){
            _original[i].push_back(new TextSnippet(*(s._original[i][j])));
        }
    }

    len = s._modified.size();
    _modified.resize(len);
    for (int i=0; i < len; i++){
        len2 = s._modified[i].size();
        for (int j=0; j < len2; j++){
            _modified[i].push_back(new TextSnippet(*(s._modified[i][j])));
        }
    }
}

void Snippet::_free()
{
    int len, len2;

    len = _original.size();
    for (int i=0; i < len; i++){
        len2 = _original[i].size();
        for (int j=0; j < len2; j++){
            delete _original[i][j];
        }
    }

    len = _modified.size();
    for (int i=0; i < len; i++){
        len2 = _modified[i].size();
        for (int j=0; j < len2; j++){
            delete _modified[i][j];
        }
    }
}

/* vim: set sw=4 ts=4 et ft=cpp : */
