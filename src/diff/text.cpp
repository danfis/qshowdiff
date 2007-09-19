#include "text.h"
#include "../settings.h"

int Text::paint(QPainter &painter, int offset, int lines) const
{
    QFontMetrics metrics(Settings::Text::font);
    int height = metrics.height();
    int descent = metrics.descent() + 1; // +1 for baseline

    // background color
    painter.setBrush(QBrush(Settings::Text::background_color));
    painter.setPen(Settings::Text::font_color);
    
    VectorOfPointers<QString>::list_iterator_t it =
        VectorOfPointers<QString>::_begin();
    VectorOfPointers<QString>::list_iterator_t it_end =
        VectorOfPointers<QString>::_end();
    int line = 0;
    for (;it != it_end; it++, line++){
        offset += height;
        painter.setPen(Settings::Text::font_color);
        painter.drawText(5, offset - descent, **it);

        //baseline:
        painter.setPen(Settings::Text::baseline_color);
        painter.drawLine(5, offset, painter.window().width(), offset);
    }
    if (line < lines)
        offset += height*(lines-line);

    return offset;
}
