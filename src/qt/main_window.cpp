#include <QSplitter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "main_window.h"
#include "diff_view.h"

MainWindow::MainWindow()
{
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    QWidget *top = new QWidget();
    DiffViewFrame *bottom = new DiffViewFrame();

    top->setMaximumHeight(100);
    splitter->addWidget(top);
    splitter->addWidget(bottom);

    setCentralWidget(splitter);
}
