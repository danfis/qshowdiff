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

#include <QTextStream>
#include <QString>
#include <list>
#include <stdio.h>

#ifndef _IN_HPP_
#define _IN_HPP_

class In {
    QTextStream *_in;
    std::list<QString> _buffer;
    bool _buffer_on;

  public:
    In(FILE *input = stdin);
    ~In();

    /**
     * Starts and end buffering input lines
     */
    void startBuff();
    void endBuff();
    void clearBuff();

    /**
     * Returns next line from input
     */
    QString line();
};

#endif
