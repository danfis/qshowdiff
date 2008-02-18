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

#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QScrollArea>
#include <QPaintEvent>
#include <vector>
using std::vector;

#include "../debug.h"
#include "../settings.h"
#include "diff_view.h"
#include "diff_view.moc"

DiffViewFrame::DiffViewFrame(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    _original = new DiffView(true);
    _modified = new DiffView(false);
    _orig = new QScrollArea();
    _modif = new QScrollArea();

    
    _orig->setWidget(_original);
    _orig->setWidgetResizable(true);
    _orig->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _modif->setWidget(_modified);
    _modif->setWidgetResizable(true);

    splitter->addWidget(_orig);
    splitter->addWidget(_modif);

    layout->addWidget(splitter);

	setLayout(layout);


    QScrollBar *orig_vertical = _orig->verticalScrollBar();
    QScrollBar *modif_vertical = _modif->verticalScrollBar();
    QScrollBar *orig_horizontal = _orig->horizontalScrollBar();
    QScrollBar *modif_horizontal = _modif->horizontalScrollBar();

    connect(orig_vertical, SIGNAL(valueChanged(int)), modif_vertical,
            SLOT(setValue(int)));
    connect(modif_vertical, SIGNAL(valueChanged(int)), orig_vertical,
            SLOT(setValue(int)));
    connect(orig_horizontal, SIGNAL(valueChanged(int)), modif_horizontal,
            SLOT(setValue(int)));
    connect(modif_horizontal, SIGNAL(valueChanged(int)), orig_horizontal,
            SLOT(setValue(int)));
}

void DiffViewFrame::changeFile(int num) const
{
    QScrollBar *sb;

    if (num != -1){
        // num - 1 is there because num==0 is for 'All files'
        _original->setCurrentFile(num - 1);
        _modified->setCurrentFile(num - 1);

        // reset sliders:
        sb = _orig->verticalScrollBar();
        sb->setValue(sb->minimum());
        sb = _orig->horizontalScrollBar();
        sb->setValue(sb->minimum());
    }
}

void DiffViewFrame::scrollDown(int how_many)
{
    QScrollBar *sb = _modif->verticalScrollBar();
    sb->setValue(sb->value() + how_many);
}

void DiffViewFrame::scrollUp(int how_many)
{
    QScrollBar *sb = _modif->verticalScrollBar();
    sb->setValue(sb->value() - how_many);
}

void DiffViewFrame::scrollLeft(int how_many)
{
    QScrollBar *sb = _modif->horizontalScrollBar();
    sb->setValue(sb->value() + how_many);
}

void DiffViewFrame::scrollRight(int how_many)
{
    QScrollBar *sb = _modif->horizontalScrollBar();
    sb->setValue(sb->value() - how_many);
}
/* DiffView */
void DiffView::paintEvent(QPaintEvent *e)
{
    painter = new QPainter(this);
    region = &e->region();

    offset = 0;
    max_width = 0;

    _paintFiles();
    
    setFixedHeight(offset);
    setMinimumWidth(max_width);
    delete painter;
}

void DiffView::setCurrentFile(int num)
{
    _current_file = num;
    repaint();
}




void DiffView::_paintFiles()
{
    if (_current_file == -1){
        Diff::const_iterator it = Diff::instance()->begin();
        Diff::const_iterator it_end = Diff::instance()->end();

        for (;it != it_end; it++){
            _paintFileHeader((*it)->getFilename());
            _paintHunks(*it);
        }
    }else{
        Diff *diff = Diff::instance();

        if (diff->numFiles() > _current_file){
            File const *file = diff->getFile(_current_file);
            _paintFileHeader(file->getFilename());
            _paintHunks(file);
        } // else do nothing
    }
}

void DiffView::_paintHunks(File const *file)
{
    File::const_iterator it = file->begin();
    File::const_iterator it_end = file->end();

    for (; it != it_end; it++){
        _paintHunkHeader();
        _paintSnippets(*it);
    }
}

void DiffView::_paintSnippets(Hunk const *hunk)
{
    int from_line;
    int height = QFontMetrics(Settings::Text::font).height();
    Hunk::const_iterator it = hunk->begin();
    Hunk::const_iterator it_end = hunk->end();
    list_of_ranges_t ranges_default;

    if (_original)
        from_line = hunk->originalBeginsAt();
    else
        from_line = hunk->modifiedBeginsAt();

    for (; it != it_end; it++){
        const ListOfTextSnippets &ts = (_original ? (*it)->getOriginal() :
                                                    (*it)->getModified());
        int len = ts.size();

        _paintSnippetBackground(*it);

        for (int i=0; i < len; i++){
            _paintLine(ts[i], from_line);
            from_line++;
        }
        
        if (_original){
            offset += height * ((*it)->numLines() - (*it)->numOriginalLines());
        }else{
            offset += height * ((*it)->numLines() - (*it)->numModifiedLines());
        }
    }
}


void DiffView::_paintLine(const TextSnippets &ts, int from_line)
{
    QFontMetrics &metrics = Settings::Text::font_metrics;
    QFontMetrics &metrics_subs = Settings::Text::font_substitution_metrics;
    QFontMetrics &metrics_ins = Settings::Text::font_insertion_metrics;

    int height = std::max(std::max(metrics.height(), metrics_subs.height()),
                          metrics_ins.height());
    QRect line_rect(0, offset, Settings::Text::line_column_width, height);
    QRect text_rect(Settings::Text::line_column_width +
            Settings::Text::line_indentation, offset, this->width(), height);
    int left = text_rect.left();
    int width;
    QString str;

    // paint lines only if they are in viewport!
    if (region->intersects(line_rect) || region->intersects(text_rect)){
        painter->setBrush(Qt::NoBrush);
        painter->setFont(Settings::Text::font);

        // draw number of line
        painter->setPen(Settings::Text::font_color);
        painter->setPen(Settings::Text::font_color);
        painter->drawText(line_rect, Qt::AlignRight,
                QString::number(from_line));

        // draw line
        TextSnippets::const_iterator it = ts.begin();
        TextSnippets::const_iterator it_end = ts.end();
        for (;it != it_end; it++){
            str = (*it)->getStr();
            // replace '\t' by eight spaces
            str.replace(QChar('\t'), QString("        "));

            switch ((*it)->getType()){
                case range_t::NOCHANGE:
                    // move text_rect to appropriate place
                    width = metrics.width(str);
                    text_rect.setLeft(left);
                    text_rect.setWidth(width);
                    left += width;

                    painter->setFont(Settings::Text::font);
                    painter->setPen(Settings::Text::font_color);
                    break;

                case range_t::DELETION:
                case range_t::INSERTION:
                    // move text_rect to appropriate place
                    width = metrics_ins.width(str);
                    text_rect.setLeft(left);
                    text_rect.setWidth(width);
                    left += width;

                    painter->setPen(Settings::Text::background_color_changed);
                    painter->setBrush(Settings::Text::brush_insertion);
                    painter->drawRect(text_rect);

                    painter->setFont(Settings::Text::font_insertion);
                    painter->setPen(Settings::Text::font_color_insertion);
                    break;

                case range_t::SUBSTITUTION:
                    // move text_rect to appropriate place
                    width = metrics_subs.width(str);
                    text_rect.setLeft(left);
                    text_rect.setWidth(width);
                    left += width;

                    painter->setPen(Settings::Text::background_color_changed);
                    painter->setBrush(Settings::Text::brush_substitution);
                    painter->drawRect(text_rect);

                    painter->setFont(Settings::Text::font_substitution);
                    painter->setPen(Settings::Text::font_color_substitution);
                    break;

                default:
                    // move text_rect to appropriate place
                    width = metrics.width(str);
                    text_rect.setLeft(left);
                    text_rect.setWidth(width);
                    left += width;

                    painter->setFont(Settings::Text::font);
                    painter->setPen(Settings::Text::font_color);
                    break;
            }
            painter->drawText(text_rect, Qt::AlignLeft, str);
        }
    }

    // increment offset
    offset += height;
    max_width = std::max(max_width, left);
}


void DiffView::_paintFileHeader(const QString &filename)
{
    QRect rect(0, offset, painter->window().width(),
            Settings::File::box_height);
    QRect text_rect(0 + Settings::File::text_left_indentation, offset,
            painter->window().width(), Settings::File::box_height);

    // paint only if is in viewport
    if (region->intersects(rect)){
        // Rectangle
        painter->setBrush(QBrush(Settings::File::background_color));
        painter->setPen(Settings::File::background_color);
        painter->drawRect(rect);

        // Text 
        painter->setFont(Settings::File::font);
        painter->setPen(Settings::File::font_color);
        painter->drawText(text_rect, Qt::AlignVCenter, "Filename: " + filename);
    }

    offset += Settings::File::box_height;
}

void DiffView::_paintHunkHeader()
{
    QRect rect(0, offset, painter->window().width(),
            Settings::Hunk::separator_height);

    // repaint only if is rect in viewport
    if (region->intersects(rect)){
        painter->setBrush(QBrush(Settings::Hunk::separator_color));
        painter->setPen(Settings::Hunk::separator_color);
        painter->drawRect(rect);
    }

    offset += Settings::Hunk::separator_height;
}

void DiffView::_paintSnippetBackground(Snippet const *snippet)
{
    int lines = snippet->numLines(); 
    int height = QFontMetrics(Settings::Text::font).height();
    QColor color;
    QRect rect(0, offset, painter->window().width(), lines*height);

    if (region->intersects(rect)){
        if (snippet->isContext()){
            color = Settings::Text::background_color;
        }else if (snippet->isAdded()){
            color = Settings::Text::background_color_added;
        }else if (snippet->isDeleted()){
            color = Settings::Text::background_color_deleted;
        }else if (snippet->isChanged()){
            color = Settings::Text::background_color_changed;
        }

        painter->setBrush(QBrush(color));
        painter->setPen(color);
        painter->drawRect(rect);
    }
}
