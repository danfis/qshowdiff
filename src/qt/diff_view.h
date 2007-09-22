#ifndef _DIFF_VIEW_H_
#define _DIFF_VIEW_H_

#include <QWidget>
#include <QSplitter>
#include <QScrollArea>
#include "../diff/diff.h"

class DiffViewFrame : public QWidget{
  public:
	DiffViewFrame(QWidget *parent = 0);
};

class DiffView : public QWidget{
  private:
    bool _original;

  public:
    DiffView(bool original, QWidget *parent = 0) : QWidget(parent),
        _original(original) {}
    void paintEvent(QPaintEvent *e);
};
#endif
