#ifndef _TEXT_H_
#define _TEXT_H_

#include <QString>
#include <vector>

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

    class iterator{
      private:
        std::vector<QString *>::const_iterator it;

      public:
        iterator(){}
        iterator(const iterator &iter) : it(iter.it){}
        iterator &operator=(const iterator& iter){ it = iter.it; return *this; }
        bool operator==(const iterator& iter){ return it == iter.it; }
        bool operator!=(const iterator& iter){ return it != iter.it; }
        iterator &operator++(){ it++; return *this; }
        iterator &operator++(int){ it++; return *this; }
        iterator &operator--(){ it--; return *this; }
        iterator &operator--(int){ it--; return *this; }
        QString operator*() const{ return **it; }

        friend iterator Text::begin() const;
        friend iterator Text::end() const;
    };
};

#endif
/* vim: set sw=4 ts=4 et ft=cpp : */
