#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QScrollArea>

#include "../debug.h"
#include "diff_view.h"
#include "diff_view.moc"

DiffViewFrame::DiffViewFrame(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    _original = new DiffView(true);
    _modified = new DiffView(false);
    QScrollArea *orig = new QScrollArea();
    QScrollArea *modif = new QScrollArea();

    
    orig->setWidget(_original);
    orig->setWidgetResizable(true);
    orig->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    modif->setWidget(_modified);
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

void DiffViewFrame::changeFile(int num) const
{
    if (num != -1){
        // num - 1 is there because num==0 is for 'All files'
        _original->setCurrentFile(num - 1);
        _modified->setCurrentFile(num - 1);
    }
}

/* DiffView */
void DiffView::paintEvent(QPaintEvent *e)
{
    int height;
    QPainter painter(this);
    if (_original){
        if (_current_file == -1)
            height = Diff::instance()->paintOriginal(painter);
        else
            height = Diff::instance()->paintOriginal(_current_file, painter);
    }else{
        if (_current_file == -1)
            height = Diff::instance()->paintModified(painter);
        else
            height = Diff::instance()->paintModified(_current_file, painter);
    }

    setFixedHeight(height);
    setMinimumWidth(Settings::max_line_width);
}

void DiffView::setCurrentFile(int num)
{
    _current_file = num;
    repaint();
}
