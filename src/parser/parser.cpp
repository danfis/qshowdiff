#include "parser.h"
#include "../diff/diff.h"

using namespace std;

Tokens::Tokens(const char *f_tok,
               const char *h_tok,
               const char *c_tok,
               const char *a_tok,
               const char *d_tok) :
    file_tok(f_tok),
    hunk_tok(h_tok),
    context_tok(c_tok),
    added_tok(a_tok),
    deleted_tok(d_tok){}

Tokens::token Tokens::match(QString &line) const
{
    if (file_tok.indexIn(line) != -1){
        return FILE_TOK;
    }else if (hunk_tok.indexIn(line) != -1){
        return HUNK_TOK;
    }else if (context_tok.indexIn(line) != -1){
        return CONTEXT_TOK;
    }else if (added_tok.indexIn(line) != -1){
        return ADDED_TOK;
    }else if (deleted_tok.indexIn(line) != -1){
        return DELETED_TOK;
    }

    return NONE_TOK;
}

TokensGit::TokensGit() : Tokens::Tokens("^diff --git a/([^ ]+) b/.*$",
                                        "^@@ -([0-9]+),.* \\+([0-9]+),.*$",
                                        "^ .*$",
                                        "^\\+.*$",
                                        "^-.*$"){}


/* PARSER */
// public:
void Parser::parse()
{
    _readNextLine();

    while (_current_state != END_STATE){
        switch (_current_state){
            case START_STATE:
                _start();
                break;
            case FILE_STATE:
                _file();
                break;
            case HUNK_STATE:
                _hunk();
                break;
            case CONTEXT_STATE:
                _context();
                break;
            case ADDED_STATE:
                _added();
                break;
            case DELETED_STATE:
                _deleted();
                break;
            case CHANGED_STATE:
                _changed();
                break;
            case END_STATE:
                _end();
                break;
        }
    }
}

void Parser::_start()
{
    if (_current_token == Tokens::FILE_TOK){
        _changeState(FILE_STATE);
    }else{
        _readNextLine();
    }
}

void Parser::_file()
{
    _finishHunk();

    if (_current_token == Tokens::FILE_TOK){
        _createNewFile();
        _readNextLine();
    }else if (_current_token == Tokens::HUNK_TOK){
        _changeState(HUNK_STATE);
    }else{
        _readNextLine();
    }
}

void Parser::_hunk()
{
    switch (_current_token){
        case Tokens::HUNK_TOK:
            _createNewHunk();
            _readNextLine();
            break;
        case Tokens::ADDED_TOK:
            _changeState(ADDED_STATE);
            break;
        case Tokens::DELETED_TOK:
            _changeState(DELETED_STATE);
            break;
        case Tokens::CONTEXT_TOK:
            _changeState(CONTEXT_STATE);
            break;
        default:
            _readNextLine();
    }
}

void Parser::_context()
{
    if (_current_token == Tokens::CONTEXT_TOK){
        _addCurrentLineToContext();
        _readNextLine();
    }else{
        _finishContext();

        switch (_current_token){
            case Tokens::FILE_TOK:
                _finishFile();
                _changeState(FILE_STATE);
                break;
            case Tokens::HUNK_TOK:
                _finishHunk();
                _changeState(HUNK_STATE);
                break;
            case Tokens::ADDED_TOK:
                _changeState(ADDED_STATE);
                break;
            case Tokens::DELETED_TOK:
                _changeState(DELETED_STATE);
                break;
            default:
                _changeState(END_STATE);
        }
    }
}

void Parser::_added()
{
    if (_current_token == Tokens::ADDED_TOK){
        _addCurrentLineToAdded();
        _readNextLine();
    }else if (_current_token == Tokens::DELETED_TOK){
        _changeState(CHANGED_STATE);
    }else{
        _finishAdded();

        switch (_current_token){
            case Tokens::FILE_TOK:
                _finishFile();
                _changeState(FILE_STATE);
                break;
            case Tokens::HUNK_TOK:
                _finishHunk();
                _changeState(HUNK_STATE);
                break;
            case Tokens::CONTEXT_TOK:
                _changeState(CONTEXT_STATE);
                break;
            default:
                _changeState(END_STATE);
        }
    }
}

void Parser::_deleted()
{
    if (_current_token == Tokens::DELETED_TOK){
        _addCurrentLineToDeleted();
        _readNextLine();
    }else if (_current_token == Tokens::ADDED_TOK){
        _changeState(CHANGED_STATE);
    }else{
        _finishDeleted();

        switch (_current_token){
            case Tokens::FILE_TOK:
                _finishFile();
                _changeState(FILE_STATE);
                break;
            case Tokens::HUNK_TOK:
                _finishHunk();
                _changeState(HUNK_STATE);
                break;
            case Tokens::CONTEXT_TOK:
                _changeState(CONTEXT_STATE);
                break;
            default:
                _changeState(END_STATE);
        }
    }
}

void Parser::_changed()
{
    if (_current_token == Tokens::DELETED_TOK){
        _addCurrentLineToDeleted();
        _readNextLine();
    }else if (_current_token == Tokens::ADDED_TOK){
        _addCurrentLineToAdded();
        _readNextLine();
    }else{
        _finishChanged();

        switch (_current_token){
            case Tokens::FILE_TOK:
                _finishFile();
                _changeState(FILE_STATE);
                break;
            case Tokens::HUNK_TOK:
                _finishHunk();
                _changeState(HUNK_STATE);
                break;
            case Tokens::CONTEXT_TOK:
                _changeState(CONTEXT_STATE);
                break;
            default:
                _changeState(END_STATE);
        }
    }
}

void Parser::_end()
{
    _finishContext();
    _finishChanged();
    _finishAdded();
    _finishDeleted();
    _finishHunk();
    _finishFile();

    _changeState(END_STATE);
}


// private:
void Parser::_readNextLine()
{
    _current_line = _in->readLine();
    if (_current_line.isNull()){
        _changeState(END_STATE);
        return;
    }

    _current_token = _tokens->match(_current_line);
    DBG("Read line \"" << _current_line.toStdString() << "\"");
}

void Parser::_changeState(Parser::states new_state)
{
    _current_state = new_state;
#ifndef NDEBUG
    string state;
    switch (_current_state){
        case START_STATE:
            state = "START_STATE";
            break;
        case FILE_STATE:
            state = "FILE_STATE";
            break;
        case HUNK_STATE:
            state = "HUNK_STATE";
            break;
        case CONTEXT_STATE:
            state = "CONTEXT_STATE";
            break;
        case ADDED_STATE:
            state = "ADDED_STATE";
            break;
        case DELETED_STATE:
            state = "DELETED_STATE";
            break;
        case CHANGED_STATE:
            state = "CHANGED_STATE";
            break;
        case END_STATE:
            state = "END_STATE";
            break;
    }
    DBG("State changed to " << state);
#endif
}


QString Parser::_capCurrentLine(int cap)
{
    switch (_current_token){
        case Tokens::FILE_TOK:
            return _tokens->file_tok.cap(cap);
        case Tokens::HUNK_TOK:
            return _tokens->hunk_tok.cap(cap);
        case Tokens::CONTEXT_TOK:
            return _tokens->context_tok.cap(cap);
        case Tokens::ADDED_TOK:
            return _tokens->added_tok.cap(cap);
        case Tokens::DELETED_TOK:
            return _tokens->deleted_tok.cap(cap);
        case Tokens::NONE_TOK:
            return "";
    }
    return "";
}

void Parser::_createNewFile()
{
    if (_cur_file != NULL){
        DBG("Can't create new file - _cur_file = " << (long)_cur_file);
        return;
    }

    Diff::instance()->addFile(_cur_file = new File(_capCurrentLine(1)));
}
void Parser::_finishFile()
{
    _cur_file = NULL;
}

void Parser::_createNewHunk()
{
    if (_cur_file == NULL || _cur_hunk != NULL){
        DBG("Can't create new hunk - _cur_hunk = " << (long)_cur_hunk
                << ", _cur_file = " << (long)_cur_file);
        return;
    }

    int from1, from2;
    from1 = _capCurrentLine(1).toInt();
    from2 = _capCurrentLine(2).toInt();

    _cur_file->addHunk(_cur_hunk = new Hunk(from1, from2));
}
void Parser::_finishHunk()
{
    _cur_hunk = NULL;
}

void Parser::_addCurrentLineToContext()
{
    if (_cur_context == NULL)
        _cur_context = new Text();
    _cur_context->addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishContext()
{
    if (_cur_context == NULL || _cur_hunk == NULL)
        return;
    _cur_hunk->addSnippet(new Context(_cur_context));
    _cur_context = NULL;
}

void Parser::_addCurrentLineToAdded()
{
    if (_cur_added == NULL)
        _cur_added = new Text();
    _cur_added->addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishAdded()
{
    if (_cur_added == NULL || _cur_hunk == NULL){
        return;
    }
    _cur_hunk->addSnippet(new Added(_cur_added));
    _cur_added = NULL;
}

void Parser::_addCurrentLineToDeleted()
{
    if (_cur_deleted == NULL)
        _cur_deleted = new Text();
    _cur_deleted->addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishDeleted()
{
    if (_cur_deleted == NULL || _cur_hunk == NULL){
        return;
    }
    _cur_hunk->addSnippet(new Deleted(_cur_deleted));
    _cur_deleted = NULL;
}

void Parser::_finishChanged()
{
    if (_cur_deleted == NULL || _cur_added == NULL || _cur_hunk == NULL){
        return;
    }
    _cur_hunk->addSnippet(new Changed(_cur_deleted, _cur_added));
    _cur_deleted = NULL;
    _cur_added = NULL;
}
/* PARSER END */



Tokens *factory(string type)
{
    Tokens *ret;

    ret = new TokensGit();
    DBG("factory(" << type << ") - ret: " << (long)ret);
    return ret;
}
