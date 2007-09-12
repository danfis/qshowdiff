#include "snippet.h"

Snippet &Snippet::operator=(const Snippet &s)
{
    _free();
    if (s._original == s._modified){
        _original = new Text(*s._original);
        _modified = _original;
    }else{
        _original = new Text(*s._original);
        _modified = new Text(*s._modified);
    }
    return *this;
}
/* vim: set sw=4 ts=4 et ft=cpp : */
