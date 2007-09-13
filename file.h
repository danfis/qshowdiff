#ifndef _FILE_H_
#define _FILE_H_

#include <QString>
#include <vector>
#include "hunk.h"

class File{
  private:
    std::vector<Hunk *> _hunks;
    QString _filename;

    void _copy(const File &);
    void _free();
  public:
    File(const char *filename) : _filename(filename){}
    File(const QString &filename) : _filename(filename){}
    File(const File &f){ _copy(f);}
    ~File(){ _free(); }
    File &operator=(const File &f){ _free(); _copy(f); return *this;}

    void addHunk(Hunk *h){ _hunks.push_back(h);}
    int numHunks() const { return _hunks.size();}
};
#endif
