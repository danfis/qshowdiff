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

#ifndef _DIFF_H_
#define _DIFF_H_

#include <vector>
#include <QString>

#include "file.h"
#include "../debug.h"

class Diff : public VectorOfPointers<File>{
  private:
    static Diff diff;

    Diff() : VectorOfPointers<File>(){}
    Diff(const Diff &d) : VectorOfPointers<File>(d){}
    Diff &operator=(const Diff &d)
        { VectorOfPointers<File>::operator=(d); return *this;}

  public:
    static Diff *instance(){ return &diff; }

    void addFile(File *f){ VectorOfPointers<File>::_add(f); }
    int numFiles() const { return VectorOfPointers<File>::_size(); }
    QString getFilename(int pos) const
        { return VectorOfPointers<File>::_get(pos)->getFilename(); }
    File const *getFile(int pos) const
        { return VectorOfPointers<File>::_get(pos); }
};

#endif
