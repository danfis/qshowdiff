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

#include "parser/in.hpp"

In::In(FILE *input)
    : _buffer_on(false)
{
    _in = new QTextStream(input);
}

In::~In()
{
    std::list<QString *>::iterator it, it_end;

    if (_in)
        delete _in;

    it = _buffer.begin();
    it_end = _buffer.end();
    for (; it != it_end; ++it){
        delete *it;
    }
    _buffer.clear();
}


void In::startBuff()
{
    _buffer_on = true;
}

void In::endBuff()
{
    _buffer_on = false;
}

QString In::line()
{
    if (_buffer_on){
        QString *line = new QString(_in->readLine());
        _buffer.push_back(line);
        return *line;
    }

    if (!_buffer.empty()){
        QString line(*_buffer.front());
        delete _buffer.front();
        _buffer.pop_front();

        return line;
    }

    return _in->readLine();
}
