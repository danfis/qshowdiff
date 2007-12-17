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

#ifndef _FILE_H_
#define _FILE_H_

#include <vector>
#include <QString>

#include "hunk.h"

class File : public VectorOfPointers<Hunk>{
  private:
    QString _filename;

    void _copy(const File &f){ _filename = f._filename; }
  public:
    File(const char *filename) : _filename(filename){}
    File(const QString &filename) : _filename(filename){}
    File(const File &f) : VectorOfPointers<Hunk>(f){ _copy(f);}
    ~File(){}
    File &operator=(const File &f){ VectorOfPointers<Hunk>::operator=(f); _copy(f); return *this;}

    void addHunk(Hunk *h){ VectorOfPointers<Hunk>::_add(h);}
    int numHunks() const { return VectorOfPointers<Hunk>::_size();}

    /**
     * Return filename.
     */
    const QString &getFilename() const { return _filename; }
};
#endif
