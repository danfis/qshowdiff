#ifndef _HUNK_H_
#define _HUNK_H_

#include <vector>

#include "snippet.h"
#include "utils.h"


/**
 * This class describes a hunk of changes from diff.
 * Hunk is aggregation of snippets.
 */
class Hunk : public VectorOfPointers<Snippet>{
  private:
    int _original_from_line;//! line on which begin changes in original file
    int _modified_from_line;//! line on which begin changes in modified file

    void _copy(const Hunk &h)
        { _original_from_line = h._original_from_line;
          _modified_from_line = h._modified_from_line; }
  public:
    Hunk(const int original_from, const int modified_from) :
        VectorOfPointers<Snippet>(),
        _original_from_line(original_from),
        _modified_from_line(modified_from){}
    Hunk(const Hunk &h) : VectorOfPointers<Snippet>(h) { _copy(h); }
    ~Hunk(){}

    Hunk &operator=(const Hunk &h)
        { VectorOfPointers<Snippet>::operator=(h); _copy(h); return *this; }

    bool operator==(const Hunk &h) const
        { return _original_from_line == h._original_from_line &&
                 _modified_from_line == h._modified_from_line &&
                 VectorOfPointers<Snippet>::operator==(h);}
    bool operator!=(const Hunk &h) const { return !(*this == h);}

    void addSnippet(Snippet *sn){ VectorOfPointers<Snippet>::_add(sn); }
    int numSnippets() const { return VectorOfPointers<Snippet>::_size(); }

    int originalBeginsAt() const { return _original_from_line;}
    int modifiedBeginsAt() const { return _modified_from_line;}
};
#endif
