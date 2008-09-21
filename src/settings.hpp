/**
 * QShowDiff
 * ----------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of QShowDiff
 *
 * QShowDiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QShowDiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QShowDiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QBrush>
#include "msg.hpp"

struct Settings{
    static int max_line_width;

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
        static QFontMetrics font_metrics;

        static QFont font_insertion;
        static QColor font_color_insertion;
        static QBrush brush_insertion;
        static QFontMetrics font_insertion_metrics;

        static QFont font_substitution;
        static QColor font_color_substitution;
        static QBrush brush_substitution;
        static QFontMetrics font_substitution_metrics;

        static QColor background_color;
        static QColor background_color_added;
        static QColor background_color_deleted;
        static QColor background_color_changed;

        static int line_column_width;
        static int line_indentation;
    };
};
#endif
