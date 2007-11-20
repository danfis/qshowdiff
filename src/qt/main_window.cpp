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
