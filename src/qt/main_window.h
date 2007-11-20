#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QKeyEvent>
#include <QListWidget>
#include "../diff/diff.h"
#include "diff_view.h"

class MainWindow : public QMainWindow{
  private:
    DiffViewFrame *_diff_view_frame;
    QListWidget *_file_list;

  public:
    MainWindow();

    void keyPressEvent(QKeyEvent *e);
};
#endif
