#include "snippet.h"
#include "../debug.h"

void Snippet::_copy(const Snippet &s)
{
    if (s._original == s._modified){
        _original = new Text(*s._original);
        _modified = _original;
    }else{
        _original = new Text(*s._original);
        _modified = new Text(*s._modified);
    }
}

int Snippet::_paint(Text *text, QPainter &painter, int offset, int from_line) const
{
    int lines = numLines(); 
    int height = QFontMetrics(Settings::Text::font).height();

    painter.setBrush(QBrush(getBackgroundColor()));
    painter.setPen(getBackgroundColor());
    painter.drawRect(0, offset, painter.window().width(), lines*height);

    offset = text->paint(painter, offset, lines, from_line);

    return offset;
}

/* vim: set sw=4 ts=4 et ft=cpp : */
