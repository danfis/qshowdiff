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

int Snippet::paintOriginal(QPainter &painter, int offset) const
{
    int lines = _original->numLines() > _modified->numLines() ?
        _original->numLines() : _modified->numLines();
 
    int height = QFontMetrics(Settings::Text::font).height();
    painter.setBrush(QBrush(getBackgroundColor()));
    painter.setPen(QColor(255,255,255));
    painter.drawRect(0, offset, painter.window().width(), lines*height);

    offset = _original->paint(painter, offset, lines);

    return offset;
}
/* vim: set sw=4 ts=4 et ft=cpp : */
