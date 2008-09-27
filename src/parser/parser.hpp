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

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <QTextStream>

#include "parser/in.hpp"
#include "diff/diff.hpp"

class Parser {
  protected:
    In &_in;

    QString _line;

    File *_cur_file;
    Hunk *_cur_hunk;
    Text _text_buffer1, _text_buffer2;

    virtual bool _nextLine();

    virtual void _clearBuffer1() { _text_buffer1.clear(); }
    virtual void _clearBuffer2() { _text_buffer2.clear(); }
    virtual void _clearBuffers() { _clearBuffer1(); _clearBuffer2(); }

    virtual void _lineToBuffer1()
        { _text_buffer1.addLine(new QString(_line)); }
    virtual void _lineToBuffer2()
        { _text_buffer2.addLine(new QString(_line)); }

    virtual inline Text &_buff1() { return _text_buffer1; }
    virtual inline Text &_buff2() { return _text_buffer2; }

    virtual void _newFile(const QString &filename = "");
    virtual void _newHunk(int from = 0, int to = 0);
    virtual void _newContext(Text &);
    virtual void _newAdded(Text &);
    virtual void _newDeleted(Text &);
    virtual void _newChanged(Text &deleted, Text &added);

  public:
    Parser(In &in);
    virtual ~Parser();

    virtual void parse() = 0;
};

#endif
