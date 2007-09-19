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
    return offset;
}


// private:

int File::_paintHeader(QPainter &painter, int offset) const
{
    QFontMetrics metrics(Settings::File::font);
    int tmp = metrics.width("Filename: ");

    // Rectangle
    painter.setBrush(QBrush(Settings::File::background_color));
    painter.setPen(QColor(255, 255, 255));
    painter.drawRect(0, offset, painter.window().width(), Settings::File::indentation*2 +
            metrics.height());

    // Text 
    offset = offset + metrics.height() + Settings::File::indentation;
    painter.setFont(Settings::File::font);
    painter.setPen(Settings::File::font_color);
    painter.drawText(5, offset - 3, "Filename: ");
    painter.drawText(5 + tmp, offset - 3, _filename);
    offset += Settings::File::indentation;

    return offset;
}
