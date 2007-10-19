#include <QSplitter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget> //TODO: change to QListWidget
#include "main_window.h"
#include "diff_view.h"

MainWindow::MainWindow()
{
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    QListWidget *top = new QListWidget();
    DiffViewFrame *bottom = new DiffViewFrame();

    DBG("getFile(0) - " << Diff::instance()->getFile(0).toStdString());
    top->insertItem(0, new QListWidgetItem("All files"));
    int len = Diff::instance()->numFiles();
    for (int i=0; i < len; i++){
        top->insertItem(i+1, new QListWidgetItem(Diff::instance()->getFile(i)));
    }

    splitter->addWidget(top);
    splitter->addWidget(bottom);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,10);

    setCentralWidget(splitter);

    connect(top, SIGNAL(currentRowChanged(int)), bottom,
            SLOT(changeFile(int)));
}
