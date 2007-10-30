#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <QTextStream>
#include <QRegExp>
#include "../diff/diff.h"

class Tokens{
  public:
    /*{*/
    /**
     * Tokens
     */
    QRegExp file_tok;
    QRegExp hunk_tok;
    QRegExp context_tok;
    QRegExp added_tok;
    QRegExp deleted_tok;
    /*}*/

  protected:
    Tokens(const char *file_tok,
           const char *hunk_tok,
           const char *context_tok,
           const char *added_tok,
           const char *deleted_tok);

  public:
    enum token{
        FILE_TOK,
        HUNK_TOK,
        CONTEXT_TOK,
        ADDED_TOK,
        DELETED_TOK,
        NONE_TOK
    };

    virtual token match(QString &line) const;
};


class TokensGit : public Tokens{
  public:
    TokensGit();
};


Tokens *factory(std::string);

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
    Text *_cur_context;
    Text *_cur_deleted;
    Text *_cur_added;

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
        _cur_file(NULL), _cur_hunk(NULL), _cur_context(NULL),
        _cur_deleted(NULL), _cur_added(NULL) { _tokens = factory(type); }
    void parse();
};

#endif
