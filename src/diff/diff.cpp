#include <QPainter>
#include "diff.h"

int Diff::paintOriginal(QPainter &painter) const
{
    VectorOfPointers<File>::list_iterator_t it =
        VectorOfPointers<File>::_begin();
    VectorOfPointers<File>::list_iterator_t it_end =
        VectorOfPointers<File>::_end();
    int offset = 0;
    for (;it != it_end; it++){
        offset = (*it)->paintOriginal(painter, offset);
    }

    return offset;
}

int Diff::paintModified(QPainter &painter) const
{
    VectorOfPointers<File>::list_iterator_t it =
        VectorOfPointers<File>::_begin();
    VectorOfPointers<File>::list_iterator_t it_end =
        VectorOfPointers<File>::_end();
    int offset = 0;
    for (;it != it_end; it++){
        offset = (*it)->paintModified(painter, offset);
    }
    
    return offset;
}

// static member
Diff Diff::diff;

