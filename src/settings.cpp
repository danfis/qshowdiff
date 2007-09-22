#include "settings.h"

QFont Settings::File::font = QFont("DejaVu Sans");
QColor Settings::File::font_color = QColor(0,0,0);
QColor Settings::File::background_color = QColor(100,100,100);
int Settings::File::box_height = 30;
int Settings::File::text_left_indentation = 10;

int Settings::Hunk::separator_height = 5;
QColor Settings::Hunk::separator_color = QColor(200, 200, 200);


QFont Settings::Text::font = QFont("DejaVu Sans");
QColor Settings::Text::font_color = QColor(0, 0, 0);

QColor Settings::Text::background_color = QColor(255, 255, 255);
QColor Settings::Text::background_color_added = QColor("#BEBEED");
QColor Settings::Text::background_color_deleted = QColor("#BEEDBE");
QColor Settings::Text::background_color_changed = QColor("#EDBEBE");

int Settings::Text::line_column_width = 30;
int Settings::Text::line_indentation = 10;
