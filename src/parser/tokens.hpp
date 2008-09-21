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

#ifndef _TOKENS_H_
#define _TOKENS_H_

#include <QRegExp>
#include <string>

#include "msg.hpp"

class Tokens;

struct TokensType {
    const char *name;
    Tokens *(*instance)();
};

extern TokensType all_tokens[];

class Tokens{
  protected:
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

    /*{*/
    /**
     * Position of elements in tokens.
     */
    int filename_pos;
    int hunk_from_original_pos;
    int hunk_from_modified_pos;
    int context_pos;
    int added_pos;
    int deleted_pos;
    /*}*/

    QString _cur_line;


    Tokens(const char *file_tok,
           int filename_pos,
           const char *hunk_tok,
           int from_original_pos,
           int from_modified_pos,
           const char *context_tok,
           int context_pos,
           const char *added_tok,
           int added_pos,
           const char *deleted_tok,
           int deleted_pos);
  public:
    enum token{
        FILE_TOK,
        HUNK_TOK,
        CONTEXT_TOK,
        ADDED_TOK,
        DELETED_TOK,
        NONE_TOK
    };

    virtual void setCurrentLine(QString &line)
        { _cur_line = line; }

    virtual token match() const;

    virtual QString getFilename()
        { return file_tok.cap(filename_pos); }

    virtual std::pair<int, int> getHunkNums()
        { return std::make_pair<int, int>
                    (hunk_tok.cap(hunk_from_original_pos).toInt(),
                     hunk_tok.cap(hunk_from_modified_pos).toInt()); }

    virtual QString getContext()
        { return context_tok.cap(context_pos); }

    virtual QString getAdded()
        { return added_tok.cap(added_pos); }

    virtual QString getDeleted()
        { return deleted_tok.cap(deleted_pos); }
};

Tokens *TokenFactory(std::string);


/** Types of input: **/

class TokensGit : public Tokens{
  public:
    TokensGit();
    static Tokens *instance() { return new TokensGit(); }
};

class TokensSvn : public Tokens{
  public:
    TokensSvn();
    static Tokens *instance() { return new TokensSvn(); }
};

class TokensDiff : public Tokens{
  public:
    TokensDiff();
    static Tokens *instance() { return new TokensDiff(); }
};

class TokensBzr : public Tokens{
  public:
    TokensBzr();
    static Tokens *instance() { return new TokensBzr(); }
};
#endif
