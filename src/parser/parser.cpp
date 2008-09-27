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

#include "parser/parser.hpp"
#include "diff/diff.hpp"

using namespace std;

Parser::Parser(In &in)
    : _in(in), _cur_file(0), _cur_hunk(0)
{
}

Parser::~Parser()
{
}

bool Parser::_nextLine()
{
    _line = _in.line();

    return !_line.isNull();
}

void Parser::_newFile(const QString &filename)
{
    _cur_file = new File(filename);
    Diff::instance()->addFile(_cur_file);
}

void Parser::_newHunk(int from, int to)
{
    if (_cur_file == 0)
        _newFile();

    _cur_hunk = new Hunk(from, to);
    _cur_file->addHunk(_cur_hunk);
}

void Parser::_newContext(Text &t)
{
    if (_cur_hunk == 0)
        _newHunk();
    _cur_hunk->addSnippet(new Context(t));
}

void Parser::_newAdded(Text &t)
{
    if (_cur_hunk == 0)
        _newHunk();
    _cur_hunk->addSnippet(new Added(t));
}

void Parser::_newDeleted(Text &t)
{
    if (_cur_hunk == 0)
        _newHunk();
    _cur_hunk->addSnippet(new Deleted(t));
}

void Parser::_newChanged(Text &deleted, Text &added)
{
    if (_cur_hunk == 0)
        _newHunk();
    _cur_hunk->addSnippet(new Changed(deleted, added));
}
