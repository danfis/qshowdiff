#ifndef _DIFF_H_
#define _DIFF_H_

#include <vector>
#include <utility>
#include <QWidget>
#include <QPaintEvent>
#include "file.h"

typedef std::pair<QWidget *, QWidget *> diff_widgets_t;
typedef std::vector<std::pair<QWidget *, QWidget *> >
    list_of_diff_widgets_t;

class Diff : public VectorOfPointers<File>{
  public:
    void addFile(File *f){ VectorOfPointers<File>::_add(f); }
    int numFiles() const { return VectorOfPointers<File>::_size(); }

    void paintOriginal(QPainter &) const;
    void paintModified(QPainter &) const;


    /**
     * Defines types of DiffWidget.
     */
    enum DiffWidgetType{ DiffWidgetTypeOriginal, DiffWidgetTypeModified };

    /**
     * Front declaration of class
     */
    template<int Type> class DiffWidget;

    /**
     * Couple typedefs for easy-using.
     */
    typedef DiffWidget<DiffWidgetTypeOriginal> DiffWidgetOriginal;
    typedef DiffWidget<DiffWidgetTypeModified> DiffWidgetModified;
    typedef std::pair<DiffWidgetOriginal *, DiffWidgetModified *> DiffWidgetPair;

    DiffWidgetPair getWidgets() const;

    /**
     * Class of Widget describing one side of diff (original or modified).
     */
    template<int Type>
    class DiffWidget : public QWidget{
      private:
        const Diff *_diff;

      public:
        DiffWidget(const Diff * diff, QWidget *parent = 0) :
            QWidget(parent), _diff(diff){}

        void paintEvent(QPaintEvent *);
    };
};

template<int Type>
void Diff::DiffWidget<Type>::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if (Type == Diff::DiffWidgetTypeOriginal){
        _diff->paintOriginal(painter);
    }else{
        _diff->paintModified(painter);
    }
}

#endif
