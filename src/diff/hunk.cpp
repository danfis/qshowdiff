#include "hunk.h"
using namespace std;

Hunk::iterator Hunk::begin() const
{
    Hunk::iterator iter;
    iter.it = _snippets.begin();
    return iter;
}
Hunk::iterator Hunk::end() const
{
    Hunk::iterator iter;
    iter.it = _snippets.end();
    return iter;
}

//private:
void Hunk::_copy(const Hunk &h)
{
    _original_from_line = h._original_from_line;
    _modified_from_line = h._modified_from_line;

    vector<Snippet *>::const_iterator it = h._snippets.begin();
    vector<Snippet *>::const_iterator it_end = h._snippets.end();
    for(;it != it_end; it++){
        _snippets.push_back(new Snippet(**it));
    }
}

void Hunk::_free()
{
    vector<Snippet *>::const_iterator it = _snippets.begin();
    vector<Snippet *>::const_iterator it_end = _snippets.end();
    for(;it != it_end; it++){
        delete *it;
    }
	_snippets.clear();
}
