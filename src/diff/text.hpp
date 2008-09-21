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

#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

#include "diff/utils.hpp"
#include "diff/levenshtein_table.hpp"

class Text : public VectorOfPointers<QString>{
  public:
    void addLine(QString *qs){ VectorOfPointers<QString>::_add(qs);}
    int numLines() const { return VectorOfPointers<QString>::_size(); }
    void clear() { VectorOfPointers<QString>::_free(); }
    bool isEmpty() const { return numLines() == 0; }

    const QString &getLine(int num) const
        { return *(VectorOfPointers<QString>::_get(num)); }
};

class TextSnippet{
  private:
    QString *str;
    range_t::range_type type;

  public:
    TextSnippet(const QString &str, range_t::range_type t) : type(t)
        { this->str = new QString(str);}
    TextSnippet(const TextSnippet &ts) : type(ts.type)
        { str = new QString(*(ts.str));}
    ~TextSnippet(){ delete str; }
    int len() const { return str->size(); }
    const QString &getStr() const { return *str; }
    range_t::range_type getType() const { return type; }

    bool operator==(const TextSnippet &ts) const { return *str == (*ts.str); }
};

typedef std::vector<TextSnippet *> TextSnippets;
typedef std::vector<TextSnippets> ListOfTextSnippets;
#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
