#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include "../diff/diff.h"

class MainWindow : public QMainWindow{
  public:
    MainWindow(Diff *);
};
#endif
