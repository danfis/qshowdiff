#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

#include "utils.h"
#include "levenshtein_table.h"

class Text : public VectorOfPointers<QString>{
  public:
    void addLine(QString *qs){ VectorOfPointers<QString>::_add(qs);}
    int numLines() const { return VectorOfPointers<QString>::_size(); }
    void clear() { VectorOfPointers<QString>::_free(); }
    bool isEmpty() const { return numLines() == 0; }

    const QString &getLine(int num) const
        { return *(VectorOfPointers<QString>::_get(num)); }
};

class TextSnippet{
  private:
    QString *str;
    range_t::range_type type;

  public:
    TextSnippet(const QString &str, range_t::range_type t) : type(t)
        { this->str = new QString(str);}
    TextSnippet(const TextSnippet &ts) : type(ts.type)
        { str = new QString(*(ts.str));}
    ~TextSnippet(){ delete str; }
    int len() const { return str->size(); }
    const QString &getStr() const { return *str; }
    range_t::range_type getType() const { return type; }

    bool operator==(const TextSnippet &ts) const { return *str == (*ts.str); }
};

typedef std::vector<TextSnippet *> TextSnippets;
typedef std::vector<TextSnippets> ListOfTextSnippets;
#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
