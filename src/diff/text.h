#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

#include "utils.h"

class Text : public VectorOfPointers<QString>{
  public:
    void addLine(QString *qs){ VectorOfPointers<QString>::_add(qs);}
    int numLines() const { return VectorOfPointers<QString>::_size(); }
};

#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
