#include <QGridLayout>
#include <QScrollBar>
#include <QPainter>

#include "diff_view.h"

DiffViewFrame::DiffViewFrame(Diff *diff, QWidget *parent) : QWidget(parent)
{
	QGridLayout *layout = new QGridLayout();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QScrollBar *bottom_scroll_bar = new QScrollBar(Qt::Horizontal);
    QScrollBar *left_scroll_bar = new QScrollBar(Qt::Vertical);

    Diff::DiffWidgetPair pair = diff->getWidgets();

    splitter->addWidget(pair.first);
    splitter->addWidget(pair.second);

    layout->addWidget(splitter, 0, 0);
    layout->addWidget(bottom_scroll_bar, 1, 0);
    layout->addWidget(left_scroll_bar, 0, 1);

	setLayout(layout);
}



/* DiffViewSplitter */
DiffViewSplitter::DiffViewSplitter(Qt::Orientation orientation, QWidget *parent) :
        QSplitter(orientation, parent)
{
    DiffView *left = new DiffView();
    DiffView *right = new DiffView();

    addWidget(left);
    addWidget(right);
}


/* DiffView */
DiffView::DiffView(QWidget *parent) : QWidget(parent)
{
}

void DiffView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(10, 10, "asdfasdf");
}
