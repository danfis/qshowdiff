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

#include "parser_big.hpp"

ParserBig::ParserBig(In &in,
              const char *tfile, const char *thunk,
              const char *tcontext, const char *tadded,
              const char *tdeleted)
    : Parser(in), _state(SStart),
      TFile(tfile), THunk(thunk), TContext(tcontext),
      TAdded(tadded), TDeleted(tdeleted)
{
}

ParserBig::~ParserBig()
{
}

void ParserBig::parse()
{
    while (_nextLine()){
        switch (_state){
            case SStart:
                _start();
                break;
            case SFile:
                _file();
                break;
            case SHunk:
                _hunk();
                break;
            case SContext:
                _matchAll();
                break;
            case SAdded:
                _matchAll();
                break;
            case SDeleted:
                _matchAll();
                break;
            case SEnd:
                break;
        }
    }
}

bool ParserBig::_matchLine(QRegExp &re)
{
    return re.exactMatch(_line);
}

QString ParserBig::_filenameFromTFile()
{
    return TFile.cap(1);
}

void ParserBig::_fromToFromTHunk(int *from, int *to)
{
    *from = THunk.cap(1).toInt();
    *to = THunk.cap(3).toInt();
}


void ParserBig::_changeState(States s)
{
    int from, to;

    // leaving SContext state -> create Context snippet
    if (_state == SContext && s != SContext){
        _newContext(_buff1());
        _clearBuffer1();
    }

    // leaving SAdded state -> create Added or Changed snippet
    if (_state == SAdded && s != SAdded && s != SDeleted){
        if (_buff1().numLines() > 0 && _buff2().numLines() > 0){
            _newChanged(_buff1(), _buff2());
        }else{
            _newAdded(_buff2());
        }

        _clearBuffer1();
        _clearBuffer2();
    }

    // leaving SDeleted state -> create Deleted or Changed snippet
    if (_state == SDeleted && s != SDeleted && s != SAdded){
        if (_buff1().numLines() > 0 && _buff2().numLines() > 0){
            _newChanged(_buff1(), _buff2());
        }else{
            _newDeleted(_buff1());
        }

        _clearBuffer1();
        _clearBuffer2();
    }

    switch (s){
        case SFile:
            _newFile(_filenameFromTFile());
            break;
        case SHunk:
            _fromToFromTHunk(&from, &to);
            _newHunk(from, to);
            break;
        case SContext:
            _lineToBuffer1();
            break;
        case SAdded:
            _lineToBuffer2();
            break;
        case SDeleted:
            _lineToBuffer1();
            break;
        default:
            break;
    }

    _state = s;
}

void ParserBig::_start()
{
    // ignore all lines until first TFile line
    if (_matchLine(TFile)){
        _changeState(SFile);
    }
}

void ParserBig::_file()
{
    // ignore all lines until first THunk line
    if (_matchLine(THunk)){
        _changeState(SHunk);
    }
}

void ParserBig::_hunk()
{
    if (_matchLine(TContext)){
        _changeState(SContext);
    }else if (_matchLine(TAdded)){
        _changeState(SAdded);
    }else if (_matchLine(TDeleted)){
        _changeState(SDeleted);
    }else if (_matchLine(TFile)){
        _changeState(SFile);
    }
}

void ParserBig::_matchAll()
{
    if (_matchLine(TFile)){
        _changeState(SFile);
    }else if (_matchLine(THunk)){
        _changeState(SHunk);
    }else if (_matchLine(TContext)){
        _changeState(SContext);
    }else if (_matchLine(TAdded)){
        _changeState(SAdded);
    }else if (_matchLine(TDeleted)){
        _changeState(SDeleted);
    }
}
