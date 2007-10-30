#include "snippet.h"
#include "../debug.h"

void Snippet::_copy(const Snippet &s)
{
    if (this == &s)
        return;

    if (s._original == s._modified){
        _original = new Text(*s._original);
        _modified = _original;
        _levenshtein = NULL;
    }else{
        _original = new Text(*s._original);
        _modified = new Text(*s._modified);
        _levenshtein = new LevenshteinDistances(*_original, *_modified);
    }
}

void Snippet::_free()
{
    if (_modified != _original){
        delete _original;
    }
    delete _modified;

    if (_levenshtein != NULL)
        delete _levenshtein;
}

/* vim: set sw=4 ts=4 et ft=cpp : */
