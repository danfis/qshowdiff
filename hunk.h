#ifndef _HUNK_H_
#define _HUNK_H_

#include <vector>

#include "snippet.h"
#include "utils.h"


/**
 * This class describes a hunk of changes from diff.
 * Hunk is aggregation of snippets.
 */
class Hunk{
  private:
    std::vector<Snippet *> _snippets;//! list of snippets
    int _original_from_line;//! line on which begin changes in original file
    int _modified_from_line;//! line on which begin changes in modified file

    void _copy(const Hunk &);
    void _free();
  public:
    class iterator; // front declaration

    Hunk(const int original_from, const int modified_from) :
        _original_from_line(original_from),
        _modified_from_line(modified_from){}
    Hunk(const Hunk &h){ _copy(h); }
    ~Hunk(){ _free(); }

    Hunk &operator=(const Hunk &h){ _free(); _copy(h); return *this; }

    void addSnippet(Snippet *sn){ _snippets.push_back(sn); }
    int numSnippets() const { return _snippets.size(); }

    int originalBeginsAt() const { return _original_from_line;}
    int modifiedBeginsAt() const { return _modified_from_line;}

    iterator begin() const;
    iterator end() const;

    /**
     * Iterator over _snippets.
     */
    class iterator : public VectorPointerIterator<Snippet>{
      public:
        friend iterator Hunk::begin() const;
        friend iterator Hunk::end() const;
    };
};
#endif
