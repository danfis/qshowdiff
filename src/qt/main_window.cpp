#include <QSplitter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "main_window.h"
#include "diff_view.h"

MainWindow::MainWindow()
{
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    QPushButton *top = new QPushButton();
    DiffViewFrame *bottom = new DiffViewFrame();

    splitter->addWidget(top);
    splitter->addWidget(bottom);

    setCentralWidget(splitter);
}
