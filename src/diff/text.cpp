#include "text.h"
#include "../settings.h"

int Text::paint(QPainter &painter, int offset, int lines, int from_line) const
{
    int height = QFontMetrics(Settings::Text::font).height();

    QRect line_rect(0, offset, Settings::Text::line_column_width, height);
    QRect text_rect(Settings::Text::line_column_width +
            Settings::Text::line_indentation, offset,
            painter.window().width(), height);
    int line = 0;

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Settings::Text::font_color);
    painter.setFont(Settings::Text::font);
    
    VectorOfPointers<QString>::list_iterator_t it =
        VectorOfPointers<QString>::_begin();
    VectorOfPointers<QString>::list_iterator_t it_end =
        VectorOfPointers<QString>::_end();
    for (;it != it_end; it++, line++){
        painter.drawText(line_rect, Qt::AlignRight,
                QString::number(from_line));
        line_rect.moveTo(line_rect.x(), line_rect.y() + height);
        from_line++;

        painter.drawText(text_rect, Qt::AlignLeft, **it);
        text_rect.moveTo(text_rect.x(), text_rect.y() + height);
        offset += height;
    }
    if (line < lines)
        offset += height*(lines-line);

    return offset;
}
