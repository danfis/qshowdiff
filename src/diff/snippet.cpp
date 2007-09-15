#include "snippet.h"

void Snippet::_copy(const Snippet &s)
{
    if (s._original == s._modified){
        _original = new Text(*s._original);
        _modified = _original;
    }else{
        _original = new Text(*s._original);
        _modified = new Text(*s._modified);
    }
}
/* vim: set sw=4 ts=4 et ft=cpp : */
