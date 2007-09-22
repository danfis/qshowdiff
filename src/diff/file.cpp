#include "file.h"
#include "../debug.h"
#include "../settings.h"

int File::paintOriginal(QPainter &painter, int offset) const
{
    offset = _paintHeader(painter, offset);

    VectorOfPointers<Hunk>::list_iterator_t it =
        VectorOfPointers<Hunk>::_begin();
    VectorOfPointers<Hunk>::list_iterator_t it_end =
        VectorOfPointers<Hunk>::_end();
    for (;it != it_end; it++){
        offset = (*it)->paintOriginal(painter, offset);
    }

    return offset;
}
int File::paintModified(QPainter &painter, int offset) const
{
    offset = _paintHeader(painter, offset);

    VectorOfPointers<Hunk>::list_iterator_t it =
        VectorOfPointers<Hunk>::_begin();
    VectorOfPointers<Hunk>::list_iterator_t it_end =
        VectorOfPointers<Hunk>::_end();
    for (;it != it_end; it++){
        offset = (*it)->paintModified(painter, offset);
    }

    return offset;
}


// private:

int File::_paintHeader(QPainter &painter, int offset) const
{
    QRect rect(0, offset, painter.window().width(),
            Settings::File::box_height);
    QRect text_rect(0 + Settings::File::text_left_indentation, offset,
            painter.window().width(), Settings::File::box_height);

    // Rectangle
    painter.setBrush(QBrush(Settings::File::background_color));
    painter.setPen(Settings::File::background_color);
    painter.drawRect(rect);

    // Text 
    painter.setFont(Settings::File::font);
    painter.setPen(Settings::File::font_color);
    painter.drawText(text_rect, Qt::AlignVCenter, "Filename: " + _filename);

    offset += Settings::File::box_height;

    return offset;
}
