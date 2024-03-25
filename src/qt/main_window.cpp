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

#include "settings.hpp"
#include "qt/main_window.hpp"

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

    _file_list->setFont(Settings::File::font);
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
    e->accept();
    DBG("Key Event: " << e->key() << " - " << e->text().toStdString());

    int key = e->key();
    Qt::KeyboardModifiers mod = e->modifiers();

    if ((key == Qt::Key_J && (mod & Qt::ShiftModifier)) || key == Qt::Key_Down){
        if (_file_list->currentRow() < _file_list->count() - 1)
            _file_list->setCurrentRow(_file_list->currentRow() + 1);

    }else if ((key == Qt::Key_K && (mod & Qt::ShiftModifier))
                    || key == Qt::Key_Up){
        if (_file_list->currentRow() != 0)
            _file_list->setCurrentRow(_file_list->currentRow() - 1);

    }else if (key == Qt::Key_J || key == Qt::Key_Enter){
        _diff_view_frame->scrollDown(10);

    }else if (key == Qt::Key_K || key == Qt::Key_Backspace){
        _diff_view_frame->scrollUp(10);

    }else if (key == Qt::Key_L || key == Qt::Key_Left){
        _diff_view_frame->scrollLeft(50);

    }else if (key == Qt::Key_H || key == Qt::Key_Right){
        _diff_view_frame->scrollRight(50);

    }else if (key == Qt::Key_Space
                || key == Qt::Key_PageDown
                || (key == Qt::Key_D && (mod & Qt::ControlModifier))){
        _diff_view_frame->scrollDown(100);

    }else if (key == Qt::Key_PageUp
                || (key == Qt::Key_U && (mod & Qt::ControlModifier))){
        _diff_view_frame->scrollUp(100);

    }else if (key == Qt::Key_Q || key == Qt::Key_Escape){
        close();
    }
}
