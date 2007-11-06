#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <exception>
#include <QTextStream>

#include "tokens.h"
#include "../diff/diff.h"

class ParserException : std::exception {
};

class Parser{
  private:
    enum states{
        START_STATE = 0,
        FILE_STATE,
        HUNK_STATE,
        CONTEXT_STATE,
        ADDED_STATE,
        DELETED_STATE,
        CHANGED_STATE,
        END_STATE
    };

    states _current_state;
    QString _current_line;
    Tokens::token _current_token;

    QTextStream *_in;
    Tokens *_tokens;

    File *_cur_file;
    Hunk *_cur_hunk;
    Text _cur_context;
    Text _cur_deleted;
    Text _cur_added;

    void _changeState(states);
    void _readNextLine();
    QString _capCurrentLine(int);

    void _createNewFile();
    void _finishFile();

    void _createNewHunk();
    void _finishHunk();

    void _addCurrentLineToContext();
    void _finishContext();
    void _addCurrentLineToAdded();
    void _finishAdded();
    void _addCurrentLineToDeleted();
    void _finishDeleted();
    void _finishChanged();

    void _start();
    void _file();
    void _hunk();
    void _context();
    void _added();
    void _deleted();
    void _changed();
    void _end();
  public:
    Parser(std::string type, QTextStream *in) :
        _current_state(START_STATE),
        _in(in),
        _cur_file(NULL), _cur_hunk(NULL)
        { _tokens = TokenFactory(type); if (_tokens == NULL) throw ParserException();}
    void parse();
};

#endif
