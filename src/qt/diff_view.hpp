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

#ifndef _DIFF_VIEW_H_
#define _DIFF_VIEW_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QScrollArea>
#include "diff/diff.hpp"

class DiffView;

class DiffViewFrame : public QWidget{
    Q_OBJECT
  private:
    DiffView *_original;
    DiffView *_modified;

    QScrollArea *_orig;
    QScrollArea *_modif;

  public:
	DiffViewFrame(QWidget *parent = 0);

    void scrollDown(int);
    void scrollUp(int);
    void scrollLeft(int);
    void scrollRight(int);

  public slots:
    /**
     * Change which file will be displayed.
     */
    void changeFile(int) const;
};

class DiffView : public QWidget{
  private:
    bool _original;

    /**
     * Number of current file. -1 if all files.
     */
    int _current_file;


    /**
     * Painting:
     */

    QPainter *painter;
    const QRegion *region; /*! region which has to be repaint */
    int offset;
    int max_width;

    void _paintFiles();
    void _paintHunks(File const *);
    void _paintSnippets(Hunk const *);
    void _paintLine(const TextSnippets &, int from_line);

    void _paintFileHeader(const QString &);
    void _paintHunkHeader();
    void _paintSnippetBackground(Snippet const *);

  public:
    DiffView(bool original, QWidget *parent = 0) : QWidget(parent),
        _original(original), _current_file(-1) {}
    void paintEvent(QPaintEvent *e);

    void setCurrentFile(int);
};
#endif
