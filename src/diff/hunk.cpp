#include "../settings.h"
#include "hunk.h"

int Hunk::paintOriginal(QPainter &painter, int offset) const
{
    painter.setBrush(QBrush(Settings::Hunk::background_color));
    painter.setPen(QColor(255,255,255));
    painter.drawRect(0, offset, painter.window().width(),
            Settings::Hunk::indentation);

    offset = offset + Settings::Hunk::indentation;

    VectorOfPointers<Snippet>::list_iterator_t it =
        VectorOfPointers<Snippet>::_begin();
    VectorOfPointers<Snippet>::list_iterator_t it_end =
        VectorOfPointers<Snippet>::_end();
    for (;it != it_end; it++){
        offset = (*it)->paintOriginal(painter, offset);
    }

    return offset;
}
