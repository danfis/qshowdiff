#ifndef _SNIPPET_H_
#define _SNIPPET_H_

#include "text.h"
#include "levenshtein_distances.h"

/**
 * Example how diff will be parsed to Snippets:
 * -------------------------------------------
 *
 *  nphier came onboard in September 2006, after } \
 *  the open source initiative had                } - Context
 *  begun. CEO Philip Rosedale, former CTO       } /
 * -at Real Networks, quickly realized          } \
 * -he needed a true open source expert to       } - Changed
 * +at Real Networks, quickly realized asdfasdf } /
 *  lead a project as complicated as } - Context
 * -open-sourcing the Second Life viewer. } - Deleted
 *  Rosedale turned to Lanphier, the          } \
 *  person who was in charge of open-sourcing  } - Context
 *  the Helix client for Real.                } /
 * +asdfasdfasdfasdasdf } - Added
 *
 */


/**
 * Base class for Context, Added, Deleted and Changed classes.
 * This class represents snippet of text of original and modified file.
 * Hunk is ordered list of snippets.
 * Class which is inherited from this class has to declare all constructors
 * as private except one (which make sense for that class) and/or has to
 * redefine original() and modified() methods if necessary.
 */
class Snippet{
  protected:
    ListOfTextSnippets _original;
    ListOfTextSnippets _modified;

    void _copy(const Snippet &);
    void _free();
    void _fromTextToTextSnippets(const Text &text, ListOfTextSnippets &ts);
    void _splitByRanges(const QString &str, const std::vector<range_t> &ranges,
                        TextSnippets &ts);

    Snippet();

  public:
    Snippet(const Text &text);
    Snippet(const Text &original, const Text &modified);
    Snippet(const Snippet &s){ _copy(s); }
    virtual ~Snippet(){ _free();}
    virtual Snippet &operator=(const Snippet &s){_free();_copy(s);return *this;}
    
    virtual bool operator==(const Snippet &s) const
        { return (_original == s._original &&
                  _modified == s._modified);}
    virtual bool operator!=(const Snippet &s) const{ return !(*this == s); }

    virtual const ListOfTextSnippets &getOriginal() const { return _original; }
    virtual const ListOfTextSnippets &getModified() const { return _modified; }

    virtual int numOriginalLines() const { return _original.size(); }
    virtual int numModifiedLines() const { return _modified.size(); }
    virtual int numLines() const { return numOriginalLines() >
        numModifiedLines() ? numOriginalLines() : numModifiedLines(); }

    virtual bool isContext() const { return false; }
    virtual bool isAdded() const { return false; }
    virtual bool isDeleted() const { return false; }
    virtual bool isChanged() const { return false; }
};

class Context : public Snippet{
  private:
    Context(const Text &t, const Text &tt) : Snippet(t,tt){}
  public:
    Context(const Text &t) : Snippet(t){}
    Context(const Context &c) : Snippet(c){}
    bool isContext() const { return true; }

    const ListOfTextSnippets &getModified() const { return _original; }
    int numModifiedLines() const { return numOriginalLines(); }
};

class Added : public Snippet{
  private:
    Added(const Text &t, const Text &tt) : Snippet(t,tt){}
  public:
    Added(const Text &t) : Snippet(t){}
    bool isAdded() const { return true; }

    const ListOfTextSnippets &getOriginal() const { return _modified; }
    int numOriginalLines() const { return _modified.size(); }
    const ListOfTextSnippets &getModified() const { return _original; }
    int numModifiedLines() const { return _original.size(); }
};


class Deleted : public Snippet{
  private:
    Deleted(const Text &t, const Text &tt) : Snippet(t,tt){}
  public:
    Deleted(const Text &t) : Snippet(t){}
    bool isDeleted() const { return true; }
};

class Changed : public Snippet{
  private:
    Changed(const Text &t) : Snippet(t){}
  public:
    Changed(const Text &t, const Text &t2) : Snippet(t,t2){}
    bool isChanged() const { return true; }
};
#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
