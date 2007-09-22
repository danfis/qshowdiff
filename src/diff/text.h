#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <QPainter>
#include <vector>

#include "utils.h"

class Text : public VectorOfPointers<QString>{
  public:
    void addLine(QString *qs){ VectorOfPointers<QString>::_add(qs);}
    int numLines() const { return VectorOfPointers<QString>::_size(); }

    int paint(QPainter &painter, int offset, int lines, int from_line) const;
};

#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
