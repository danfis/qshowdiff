#include "settings.h"

QFont Settings::File::font = QFont("DejaVu Sans");
QColor Settings::File::font_color = QColor(0,0,0);
QColor Settings::File::background_color = QColor(100,100,100);
int Settings::File::indentation = 10;

QFont Settings::Hunk::font = QFont("DejaVu Sans");
QColor Settings::Hunk::font_color = QColor(0,0,0);
QColor Settings::Hunk::background_color = QColor(200,200,200);
int Settings::Hunk::indentation = 5;

QFont Settings::Text::font = QFont("DejaVu Sans");
QColor Settings::Text::font_color = QColor(0, 0, 0);
QColor Settings::Text::background_color = QColor(255, 255, 255);
QColor Settings::Text::background_color_added = QColor(100, 25, 255);
QColor Settings::Text::baseline_color = QColor(100, 100, 100, 50);
