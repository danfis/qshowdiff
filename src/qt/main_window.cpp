#include <QSplitter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "main_window.h"
#include "diff_view.h"

MainWindow::MainWindow(Diff *diff)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    QPushButton *top = new QPushButton();
    DiffViewFrame *bottom = new DiffViewFrame(diff);

    splitter->addWidget(top);
    splitter->addWidget(bottom);

    setCentralWidget(splitter);
}
