#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include "debug.h"

struct Settings{
    struct File{
        static QFont font;
        static QColor font_color;
        static QColor background_color;
        static int indentation;
    };

    struct Hunk{
        static QFont font;
        static QColor font_color;
        static QColor background_color;
        static int indentation;
    };

    struct Text{
        static QFont font;
        static QColor font_color;
        static QColor background_color;
        static QColor background_color_added;
        static QColor baseline_color;
    };
};
#endif
