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
        static int box_height;
        static int text_left_indentation;
    };

    struct Hunk{
        static int separator_height;
        static QColor separator_color;
    };

    struct Text{
        static QFont font;
        static QColor font_color;

        static QColor background_color;
        static QColor background_color_added;
        static QColor background_color_deleted;
        static QColor background_color_changed;

        static int line_column_width;
        static int line_indentation;
    };
};
#endif
