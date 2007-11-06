#ifndef _DIFF_VIEW_H_
#define _DIFF_VIEW_H_

#include <QWidget>
#include <QSplitter>
#include <QScrollArea>
#include "../diff/diff.h"

class DiffView;

class DiffViewFrame : public QWidget{
    Q_OBJECT
  private:
    DiffView *_original;
    DiffView *_modified;


  public:
	DiffViewFrame(QWidget *parent = 0);

  public slots:
    /**
     * Change which file will be displayed.
     */
    void changeFile(int) const;
};

class DiffView : public QWidget{
  private:
    bool _original;

    /**
     * Number of current file. -1 if all files.
     */
    int _current_file;


    /**
     * Painting:
     */

    QPainter *painter;
    int offset;
    int max_width;

    void _paintFiles();
    void _paintHunks(File const *);
    void _paintSnippets(Hunk const *);
    void _paintLine(const TextSnippets &, int from_line);

    void _paintFileHeader(const QString &);
    void _paintHunkHeader();
    void _paintSnippetBackground(Snippet const *);

  public:
    DiffView(bool original, QWidget *parent = 0) : QWidget(parent),
        _original(original), _current_file(-1) {}
    void paintEvent(QPaintEvent *e);

    void setCurrentFile(int);
};
#endif
