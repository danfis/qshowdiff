#include "file.h"
using namespace std;

//private:
void File::_copy(const File &f)
{
    _filename = f._filename;

    vector<Hunk *>::const_iterator it = f._hunks.begin();
    vector<Hunk *>::const_iterator it_end = f._hunks.end();
    for (;it != it_end; it++){
        _hunks.push_back(new Hunk(**it));
    }
}

void File::_free()
{
    vector<Hunk *>::const_iterator it = _hunks.begin();
    vector<Hunk *>::const_iterator it_end = _hunks.end();
    for (;it != it_end; it++){
        delete *it;
    }
    _hunks.clear();
}
