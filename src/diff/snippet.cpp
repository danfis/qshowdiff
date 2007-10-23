#include "snippet.h"
#include "../debug.h"

void Snippet::_copy(const Snippet &s)
{
    if (this == &s)
        return;

    if (s._original == s._modified){
        _original = new Text(*s._original);
        _modified = _original;
        _levenshtein = NULL;
    }else{
        _original = new Text(*s._original);
        _modified = new Text(*s._modified);
        _levenshtein = new LevenshteinDistances(*_original, *_modified);
    }
}

void Snippet::_free()
{
    if (_modified != _original){
        delete _original;
    }
    delete _modified;

    if (_levenshtein != NULL)
        delete _levenshtein;
}
int Snippet::_paint(Text *text, QPainter &painter, int offset, int from_line) const
{
    int lines = numLines(); 
    int height = QFontMetrics(Settings::Text::font).height();

    painter.setBrush(QBrush(getBackgroundColor()));
    painter.setPen(getBackgroundColor());
    painter.drawRect(0, offset, painter.window().width(), lines*height);

    if (_levenshtein == NULL){
        offset = text->paint(painter, offset, lines, from_line);
    }else{
        if (text == _original)
            offset = text->paint(painter, offset, lines, from_line,
                                 _levenshtein->getRangesOriginal());
        if (text == _modified)
            offset = text->paint(painter, offset, lines, from_line,
                                 _levenshtein->getRangesModified());
    }

    return offset;
}

/* vim: set sw=4 ts=4 et ft=cpp : */
