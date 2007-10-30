#ifndef _DIFF_H_
#define _DIFF_H_

#include <vector>
#include <QString>

#include "file.h"
#include "../debug.h"

typedef std::pair<QWidget *, QWidget *> diff_widgets_t;
typedef std::vector<std::pair<QWidget *, QWidget *> >
    list_of_diff_widgets_t;

class Diff : public VectorOfPointers<File>{
  private:
    static Diff diff;

    Diff() : VectorOfPointers<File>(){}
    Diff(const Diff &d) : VectorOfPointers<File>(d){}
    Diff &operator=(const Diff &d)
        { VectorOfPointers<File>::operator=(d); return *this;}

  public:
    static Diff *instance(){ return &diff; }

    void addFile(File *f){ VectorOfPointers<File>::_add(f); }
    int numFiles() const { return VectorOfPointers<File>::_size(); }
    QString getFilename(int pos) const
        { return VectorOfPointers<File>::_get(pos)->getFilename(); }
    File const *getFile(int pos) const
        { return VectorOfPointers<File>::_get(pos); }
};

#endif
