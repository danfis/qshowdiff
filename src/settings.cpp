#include "settings.h"

int Settings::max_line_width = 0;

QFont Settings::File::font = QFont("DejaVu Sans");
QColor Settings::File::font_color = QColor(0,0,0);
QColor Settings::File::background_color = QColor(100,100,100);
int Settings::File::box_height = 30;
int Settings::File::text_left_indentation = 10;

int Settings::Hunk::separator_height = 5;
QColor Settings::Hunk::separator_color = QColor(200, 200, 200);


QFont Settings::Text::font = QFont("DejaVu Sans");
QColor Settings::Text::font_color = QColor(0, 0, 0);
QFontMetrics Settings::Text::font_metrics =
        QFontMetrics(Settings::Text::font);

QFont Settings::Text::font_insertion = QFont("DejaVu Sans", -1,
                                            QFont::Bold);
QColor Settings::Text::font_color_insertion = Settings::Text::font_color;
QBrush Settings::Text::brush_insertion = QBrush(QColor(100,100,100),
                                               Qt::DiagCrossPattern);
QFontMetrics Settings::Text::font_insertion_metrics =
        QFontMetrics(Settings::Text::font_insertion);

QFont Settings::Text::font_substitution = Settings::Text::font_insertion;
QColor Settings::Text::font_color_substitution = Settings::Text::font_color;
QBrush Settings::Text::brush_substitution = QBrush(QColor(50, 50, 50),
                                                   Qt::Dense7Pattern);
QFontMetrics Settings::Text::font_substitution_metrics =
        QFontMetrics(Settings::Text::font_substitution);

QColor Settings::Text::background_color = QColor(255, 255, 255);
QColor Settings::Text::background_color_added = QColor("#BEBEED");
QColor Settings::Text::background_color_deleted = QColor("#BEEDBE");
QColor Settings::Text::background_color_changed = QColor("#EDBEBE");

int Settings::Text::line_column_width = 30;
int Settings::Text::line_indentation = 10;
