/**
 * QShowDiff
 * ----------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of QShowDiff
 *
 * QShowDiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QShowDiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QShowDiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "parser.h"
#include "../diff/diff.h"

using namespace std;

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
                break;
        }
    }
    _end();
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
        _finishFile();
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
        _current_token = Tokens::NONE_TOK;
        return;
    }

    _current_token = _tokens->match(_current_line);
    DBG("Read line \"" << _current_line.toStdString() << "\" --> current token:" << _current_token);
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
    int pos;

    if (_cur_file != NULL){
        DBG("Can't create new file - _cur_file = " << (long)_cur_file);
        return;
    }

    pos = _tokens->getFilenamePos();
    Diff::instance()->addFile(_cur_file = new File(_capCurrentLine(pos)));
}
void Parser::_finishFile()
{
    _cur_file = NULL;
}

void Parser::_createNewHunk()
{
    int pos1, pos2;
    int from1, from2;

    if (_cur_file == NULL || _cur_hunk != NULL){
        DBG("Can't create new hunk - _cur_hunk = " << (long)_cur_hunk
                << ", _cur_file = " << (long)_cur_file);
        return;
    }

    pos1 = _tokens->getHunkFromOriginalPos();
    pos2 = _tokens->getHunkFromModifiedPos();
    from1 = _capCurrentLine(pos1).toInt();
    from2 = _capCurrentLine(pos2).toInt();

    _cur_file->addHunk(_cur_hunk = new Hunk(from1, from2));
}
void Parser::_finishHunk()
{
    _cur_hunk = NULL;
}

void Parser::_addCurrentLineToContext()
{
    //if (_cur_context == NULL)
    //    _cur_context = new Text();
    _cur_context.addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishContext()
{
    if (_cur_context.isEmpty() || _cur_hunk == NULL)
        return;
    _cur_hunk->addSnippet(new Context(_cur_context));
    _cur_context.clear();
}

void Parser::_addCurrentLineToAdded()
{
    //if (_cur_added == NULL)
    //    _cur_added = new Text();
    _cur_added.addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishAdded()
{
    if (_cur_added.isEmpty() || _cur_hunk == NULL){
        return;
    }
    _cur_hunk->addSnippet(new Added(_cur_added));
    _cur_added.clear();
}

void Parser::_addCurrentLineToDeleted()
{
    //if (_cur_deleted == NULL)
    //    _cur_deleted = new Text();
    _cur_deleted.addLine(new QString(_current_line.remove(0,1)));
}
void Parser::_finishDeleted()
{
    if (_cur_deleted.isEmpty() || _cur_hunk == NULL){
        return;
    }
    _cur_hunk->addSnippet(new Deleted(_cur_deleted));
    _cur_deleted.clear();
}

void Parser::_finishChanged()
{
    if (_cur_deleted.isEmpty() || _cur_added.isEmpty() || _cur_hunk == NULL){
        return;
    }

    DBG("Finish changed:");
    DBG("added: " << _cur_added.getLine(0).toStdString());
    DBG("deleted: " << _cur_deleted.getLine(0).toStdString());
    _cur_hunk->addSnippet(new Changed(_cur_deleted, _cur_added));
    _cur_deleted.clear();
    _cur_added.clear();
}
/* PARSER END */

