#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

#include "utils.h"

class Text{
  private:
    std::vector<QString *> _text;

    void free();
    void copy(const Text &);

  public:
    class iterator; // front declaration

    Text(){}
    Text(const Text &t);
    ~Text();

    Text &operator=(const Text &);
    bool operator==(const Text &t) const;
    bool operator!=(const Text &t) const { return !(*this == t); }

    void addLine(QString *);
    int numLines() const { return _text.size(); }

    iterator begin() const;
    iterator end() const;

    class iterator : public VectorPointerIterator<QString>{
      public:
        friend iterator Text::begin() const;
        friend iterator Text::end() const;
    };
};

#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
