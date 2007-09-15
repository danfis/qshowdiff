#ifndef _DIFF_H_
#define _DIFF_H_

#include <vector>
#include "file.h"

class Diff : public VectorOfPointers<File>{
  public:
    void addFile(File *f){ VectorOfPointers<File>::_add(f); }
    int numFiles() const { return VectorOfPointers<File>::_size(); }
};

#endif
