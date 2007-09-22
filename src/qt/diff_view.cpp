#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QScrollArea>

#include "../debug.h"
#include "diff_view.h"

DiffViewFrame::DiffViewFrame(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    DiffView *original = new DiffView(true);
    DiffView *modified = new DiffView(false);
    QScrollArea *orig = new QScrollArea();
    QScrollArea *modif = new QScrollArea();

    
    orig->setWidget(original);
    orig->setWidgetResizable(true);
    orig->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    modif->setWidget(modified);
    modif->setWidgetResizable(true);

    splitter->addWidget(orig);
    splitter->addWidget(modif);

    layout->addWidget(splitter);

	setLayout(layout);


    QScrollBar *orig_vertical = orig->verticalScrollBar();
    QScrollBar *modif_vertical = modif->verticalScrollBar();
    QScrollBar *orig_horizontal = orig->horizontalScrollBar();
    QScrollBar *modif_horizontal = modif->horizontalScrollBar();

    connect(orig_vertical, SIGNAL(valueChanged(int)), modif_vertical,
            SLOT(setValue(int)));
    connect(modif_vertical, SIGNAL(valueChanged(int)), orig_vertical,
            SLOT(setValue(int)));
    connect(orig_horizontal, SIGNAL(valueChanged(int)), modif_horizontal,
            SLOT(setValue(int)));
    connect(modif_horizontal, SIGNAL(valueChanged(int)), orig_horizontal,
            SLOT(setValue(int)));
}


/* DiffView */
void DiffView::paintEvent(QPaintEvent *e)
{
    int height;
    QPainter painter(this);
    if (_original){
        height = Diff::instance()->paintOriginal(painter);
    }else{
        height = Diff::instance()->paintModified(painter);
    }

    setFixedHeight(height);
    setMinimumWidth(Settings::max_line_width);
}
