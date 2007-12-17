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

#include "../debug.h"

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

    /*{*/
    /**
     * Position of elements in tokens.
     */
    int filename_pos;
    int hunk_from_original_pos;
    int hunk_from_modified_pos;
    /*}*/

  protected:
    Tokens(const char *file_tok,
           int filename_pos,
           const char *hunk_tok,
           int from_original_pos,
           int from_modified_pos,
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
    virtual int getFilenamePos() const { return filename_pos; }
    virtual int getHunkFromOriginalPos() const
        { return hunk_from_original_pos; }
    virtual int getHunkFromModifiedPos() const
        { return hunk_from_modified_pos; }
};

class TokensGit : public Tokens{
  public:
    TokensGit();
};

class TokensSvn : public Tokens{
  public:
    TokensSvn();
};

Tokens *TokenFactory(std::string);
#endif
