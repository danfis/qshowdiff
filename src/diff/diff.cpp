#include <QPainter>
#include "diff.h"
using std::pair;

Diff::DiffWidgetPair Diff::getWidgets() const
{
    Diff::DiffWidgetOriginal *original = new DiffWidgetOriginal(this);
    Diff::DiffWidgetModified *modified = new DiffWidgetModified(this);
    return Diff::DiffWidgetPair(original, modified);
}

void Diff::paintOriginal(QPainter &painter) const
{
    VectorOfPointers<File>::list_iterator_t it =
        VectorOfPointers<File>::_begin();
    VectorOfPointers<File>::list_iterator_t it_end =
        VectorOfPointers<File>::_end();
    int offset = 0;
    for (;it != it_end; it++){
        offset = (*it)->paintOriginal(painter, offset);
    }
}

void Diff::paintModified(QPainter &painter) const
{
    VectorOfPointers<File>::list_iterator_t it =
        VectorOfPointers<File>::_begin();
    VectorOfPointers<File>::list_iterator_t it_end =
        VectorOfPointers<File>::_end();
    int offset = 0;
    for (;it != it_end; it++){
        offset = (*it)->paintModified(painter, offset);
    }
}
