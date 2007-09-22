#ifndef _SNIPPET_H_
#define _SNIPPET_H_

#include "../settings.h"
#include "text.h"

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
    Text *_original;
    Text *_modified;

    void _copy(const Snippet &);
    void _free(){ if (_modified != _original){delete _original;}
                  delete _modified;}

    /**
     * Paint text by painter on offset (from beginning). from_line is
     * number of line, where text begin.
     */
    virtual int _paint(Text *text, QPainter &painter, int offset,
                       int from_line) const;

    Snippet();

  public:
    Snippet(Text *text) : _original(text), _modified(text){}
    Snippet(Text *original, Text *modified) : _original(original),
            _modified(modified){}
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
    virtual Text original() const{ return *_original;}

    /**
     * Returns text from modified file.
     */
    virtual Text modified() const{ return *_modified;}


    virtual int paintOriginal(QPainter &painter, int offset, int from_line) const
        { return _paint(_original, painter, offset, from_line); }
    virtual int paintModified(QPainter &painter, int offset, int from_line) const
        { return _paint(_modified, painter, offset, from_line); }
    virtual QColor &getBackgroundColor() const
        { return Settings::Text::background_color; }

    virtual int numOriginalLines() const { return _original->numLines(); }
    virtual int numModifiedLines() const { return _modified->numLines(); }
    virtual int numLines() const { return numOriginalLines() >
        numModifiedLines() ? numOriginalLines() : numModifiedLines(); }
};

class Context : public Snippet{
  private:
    Context(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Context(Text *t) : Snippet(t){}
    Context(const Context &c) : Snippet(c){}
};

class Added : public Snippet{
  private:
    Added(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Added(Text *t) : Snippet(t){ _original = new Text();}
    Text original() const{ return Text();}
    QColor &getBackgroundColor() const
        { return Settings::Text::background_color_added;}
};


class Deleted : public Snippet{
  private:
    Deleted(Text *t, Text *tt) : Snippet(t,tt){}
  public:
    Deleted(Text *t) : Snippet(t){ _modified = new Text(); }
    Text modified() const{ return Text();}
    QColor &getBackgroundColor() const
        { return Settings::Text::background_color_deleted;}
};

class Changed : public Snippet{
  private:
    Changed(Text *t) : Snippet(t){}
  public:
    Changed(Text *t, Text *t2) : Snippet(t,t2){}
    QColor &getBackgroundColor() const
        { return Settings::Text::background_color_changed;}
};
#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
