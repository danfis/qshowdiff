#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

#include "utils.h"
#include "levenshtein_table.h"

class Text : public VectorOfPointers<QString>{
  public:
    void addLine(QString *qs){ VectorOfPointers<QString>::_add(qs);}
    int numLines() const { return VectorOfPointers<QString>::_size(); }

    const QString &getLine(int num) const
        { return *(VectorOfPointers<QString>::_get(num)); }
};

#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
