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

#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <exception>
#include <QTextStream>

#include "tokens.h"
#include "in.hpp"
#include "../diff/diff.h"

class ParserException : std::exception {
};

class Parser{
  private:
    enum states{
        START_STATE = 0,
        FILE_STATE,
        HUNK_STATE,
        CONTEXT_STATE,
        ADDED_STATE,
        DELETED_STATE,
        CHANGED_STATE,
        END_STATE
    };

    states _current_state;
    QString _current_line;
    Tokens::token _current_token;

    In &_in;
    Tokens *_tokens;

    File *_cur_file;
    Hunk *_cur_hunk;
    Text _cur_context;
    Text _cur_deleted;
    Text _cur_added;

    void _changeState(states);
    void _readNextLine();

    void _createNewFile();

    void _createNewHunk();

    void _addCurrentLineToContext();
    void _finishContext();
    void _addCurrentLineToAdded();
    void _finishAdded();
    void _addCurrentLineToDeleted();
    void _finishDeleted();
    void _finishChanged();

    void _start();
    void _file();
    void _hunk();
    void _context();
    void _added();
    void _deleted();
    void _changed();
    void _end();
  public:
    Parser(std::string type, In &in) :
        _current_state(START_STATE),
        _in(in),
        _cur_file(NULL), _cur_hunk(NULL)
        { _tokens = TokenFactory(type); if (_tokens == NULL) throw ParserException();}
    void parse();
};

#endif
