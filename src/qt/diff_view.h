#ifndef _DIFF_VIEW_H_
#define _DIFF_VIEW_H_

#include <QWidget>
#include <QSplitter>

class DiffViewFrame : public QWidget{
  public:
	DiffViewFrame(QWidget *parent = 0);
};


class DiffViewSplitter : public QSplitter{
  public:
    DiffViewSplitter(Qt::Orientation orientation, QWidget *parent = 0);
};


class DiffView : public QWidget{
  public:
    DiffView(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
};
#endif
