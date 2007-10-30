#ifndef _FILE_H_
#define _FILE_H_

#include <vector>
#include <QString>

#include "hunk.h"

class File : public VectorOfPointers<Hunk>{
  private:
    QString _filename;

    void _copy(const File &f){ _filename = f._filename; }

    int _paintHeader(QPainter &original, int offset) const;
  public:
    File(const char *filename) : _filename(filename){}
    File(const QString &filename) : _filename(filename){}
    File(const File &f) : VectorOfPointers<Hunk>(f){ _copy(f);}
    ~File(){}
    File &operator=(const File &f){ VectorOfPointers<Hunk>::operator=(f); _copy(f); return *this;}

    void addHunk(Hunk *h){ VectorOfPointers<Hunk>::_add(h);}
    int numHunks() const { return VectorOfPointers<Hunk>::_size();}

    /**
     * Return filename.
     */
    const QString &getFilename() const { return _filename; }
};
#endif
