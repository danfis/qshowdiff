#include "../settings.h"
#include "hunk.h"

int Hunk::_paintSeparator(QPainter &painter, int offset) const
{
    painter.setBrush(QBrush(Settings::Hunk::separator_color));
    painter.setPen(Settings::Hunk::separator_color);
    painter.drawRect(0, offset, painter.window().width(),
            Settings::Hunk::separator_height);

    return offset + Settings::Hunk::separator_height;
}


int Hunk::paintOriginal(QPainter &painter, int offset) const
{
    int num_line = _original_from_line;
    offset = _paintSeparator(painter, offset);

    VectorOfPointers<Snippet>::list_iterator_t it =
        VectorOfPointers<Snippet>::_begin();
    VectorOfPointers<Snippet>::list_iterator_t it_end =
        VectorOfPointers<Snippet>::_end();
    for (;it != it_end; it++){
        offset = (*it)->paintOriginal(painter, offset, num_line);
        num_line += (*it)->numOriginalLines();
    }

    return offset;
}

int Hunk::paintModified(QPainter &painter, int offset) const
{
    int num_line = _original_from_line;
    offset = _paintSeparator(painter, offset);

    VectorOfPointers<Snippet>::list_iterator_t it =
        VectorOfPointers<Snippet>::_begin();
    VectorOfPointers<Snippet>::list_iterator_t it_end =
        VectorOfPointers<Snippet>::_end();
    for (;it != it_end; it++){
        offset = (*it)->paintModified(painter, offset, num_line);
        num_line += (*it)->numModifiedLines();
    }

    return offset;
}
