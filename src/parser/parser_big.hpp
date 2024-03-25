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

#ifndef _PARSER_BIG_HPP_
#define _PARSER_BIG_HPP_

#include <QtCore5Compat/QRegExp>
#include "parser/parser.hpp"

class ParserBig : public Parser {
  protected:
    enum States{
        SStart = 0,
        SFile,
        SHunk,
        SContext,
        SAdded,
        SDeleted,
        SEnd
    };

    States _state;

    QRegExp TFile;
    QRegExp THunk;
    QRegExp TContext;
    QRegExp TAdded;
    QRegExp TDeleted;

    virtual bool _matchLine(QRegExp &);
    virtual QString _filenameFromTFile();
    virtual void _fromToFromTHunk(int *from, int *to);
    virtual void _changeState(States s);

    virtual void _start();
    virtual void _file();
    virtual void _hunk();
    virtual void _matchAll();

    virtual void _lineToBuffer1()
        { _buff1().addLine(new QString(_line.mid(1))); }
    virtual void _lineToBuffer2()
        { _buff2().addLine(new QString(_line.mid(1))); }

  public:
    ParserBig(In &in,
              const char *tfile, const char *thunk,
              const char *tcontext, const char *tadded,
              const char *tdeleted);
    ~ParserBig();

    void parse();
};

#endif
