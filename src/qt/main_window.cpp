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

#include <QSplitter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "main_window.h"

MainWindow::MainWindow()
{
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    _file_list = new QListWidget();
    _diff_view_frame = new DiffViewFrame();

    _file_list->insertItem(0, new QListWidgetItem("All files"));
    int len = Diff::instance()->numFiles();
    DBG("Num files in Diff: " << len);
    for (int i=0; i < len; i++){
        _file_list->insertItem(i+1,
                new QListWidgetItem(Diff::instance()->getFilename(i)));
    }

    _file_list->setCurrentRow(0);

    splitter->addWidget(_file_list);
    splitter->addWidget(_diff_view_frame);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,10);

    setCentralWidget(splitter);

    connect(_file_list, SIGNAL(currentRowChanged(int)), _diff_view_frame,
            SLOT(changeFile(int)));

    resize(800, 600);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    int key;

    e->accept();
    DBG("Key Event: " << e->key() << " - " << e->text().toStdString());

    key = e->key();
    switch (key){
        case 16777220: // enter
            _diff_view_frame->scrollDown(10);
            break;
        case 16777219: // backspace
            _diff_view_frame->scrollUp(10);
            break;

        case 32: // space
            _diff_view_frame->scrollDown(100);
            break;

        case 16777238: // pgup
            _diff_view_frame->scrollUp(100);
            break;
        case 16777239: // pgdown
            _diff_view_frame->scrollDown(100);
            break;

        case 16777236: //left
            _diff_view_frame->scrollLeft(50);
            break;
        case 16777234:
            _diff_view_frame->scrollRight(50);
            break;

        case 16777235: // up
            if (_file_list->currentRow() != 0)
                _file_list->setCurrentRow(_file_list->currentRow() - 1);
            break;
        case 16777237: // down
            if (_file_list->currentRow() < _file_list->count() - 1)
                _file_list->setCurrentRow(_file_list->currentRow() + 1);
            break;

    }
}
