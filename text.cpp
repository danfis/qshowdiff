#include "text.h"
using namespace std;

Text::Text(const Text &t)
{
    copy(t);
}

Text::~Text()
{
    free();
}

Text & Text::operator=(const Text &t)
{
    free();
    copy(t);
    return *this;
}

bool Text::operator==(const Text &t) const
{
    if (_text.size() != t._text.size())
        return false;

    // _text and t._text has same length so no t._text.end() is needed
    vector<QString *>::const_iterator it = _text.begin();
    vector<QString *>::const_iterator it_end = _text.end();
    vector<QString *>::const_iterator it2 = t._text.begin();

    for (;it != it_end; it++, it2++){
        if (**it != **it2)
            return false;
    }

    return true;
}

void Text::add(QString *qs)
{
    _text.push_back(qs);
}


Text::iterator Text::begin() const
{
    iterator iter;
    iter.it = _text.begin();
    return iter;
}

Text::iterator Text::end() const
{
    iterator iter;
    iter.it = _text.end();
    return iter;
}


//private:
void Text::free()
{
    vector<QString *>::const_iterator it = _text.begin();
    vector<QString *>::const_iterator it_end = _text.end();

    for(;it != it_end; it++){
        delete *it;
    }
}

void Text::copy(const Text &t)
{
    vector<QString *>::const_iterator it = t._text.begin();
    vector<QString *>::const_iterator it_end = t._text.end();

    for (;it != it_end; it++){
        _text.push_back(new QString(**it));
    }
}
