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

//TODO: Create Levenshtein distance class for Changed class.
//      Levenshtein distance must be computed during creating a class, not
//      during printing!

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
    Text *_original;
    Text *_modified;

    LevenshteinDistances *_levenshtein;

    void _copy(const Snippet &);
    void _free();

    Snippet();

  public:
    Snippet(Text *text) : _original(text), _modified(text),
        _levenshtein(NULL){}
    Snippet(Text *original, Text *modified) : _original(original),
            _modified(modified)
            { _levenshtein = new LevenshteinDistances(*original, *modified);}
    Snippet(const Snippet &s){ _copy(s); }
    virtual ~Snippet(){ _free();}
    virtual Snippet &operator=(const Snippet &s){_free();_copy(s);return *this;}
    
    virtual bool operator==(const Snippet &s) const
        { return (*_original == *(s._original) &&
                  *_modified == *(s._modified) &&
                  (_original == _modified) == (s._original == s._modified));}
    virtual bool operator!=(const Snippet &s) const{ return !(*this == s); }

    /**
     * Returns text from original file.
     */
    virtual const Text *getOriginal() const{ return _original;}

    /**
     * Returns text from modified file.
     */
    virtual const Text *getModified() const{ return _modified;}


    virtual int numOriginalLines() const { return _original->numLines(); }
    virtual int numModifiedLines() const { return _modified->numLines(); }
    virtual int numLines() const { return numOriginalLines() >
        numModifiedLines() ? numOriginalLines() : numModifiedLines(); }

    virtual bool isContext() const { return false; }
    virtual bool isAdded() const { return false; }
    virtual bool isDeleted() const { return false; }
    virtual bool isChanged() const { return false; }
};

class Context : public Snippet{
  private:
    Context(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Context(Text *t) : Snippet(t){}
    Context(const Context &c) : Snippet(c){}
    bool isContext() const { return true; }
};

class Added : public Snippet{
  private:
    Added(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Added(Text *t) : Snippet(t){ _original = new Text();}
    bool isAdded() const { return true; }
};


class Deleted : public Snippet{
  private:
    Deleted(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Deleted(Text *t) : Snippet(t){ _modified = new Text(); }
    bool isDeleted() const { return true; }
};

class Changed : public Snippet{
  private:
    Changed(Text *t) : Snippet(t){}
  public:
    Changed(Text *t, Text *t2) : Snippet(t,t2){}
    bool isChanged() const { return true; }
};
#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
