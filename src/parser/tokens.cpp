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

#include "tokens.h"
using std::string;

Tokens *TokenFactory(string type)
{
    Tokens *ret = NULL;

    if (type == "git"){
        ret = new TokensGit();
    }else if (type == "svn"){
        ret = new TokensSvn();
    }

    DBG("factory(" << type << ") - ret: " << (long)ret);
    return ret;
}


Tokens::Tokens(const char *f_tok,
               int fname_pos,
               const char *h_tok,
               int from_orig_pos,
               int from_modif_pos,
               const char *c_tok,
               const char *a_tok,
               const char *d_tok) :
    file_tok(f_tok),
    hunk_tok(h_tok),
    context_tok(c_tok),
    added_tok(a_tok),
    deleted_tok(d_tok),

    filename_pos(fname_pos),
    hunk_from_original_pos(from_orig_pos),
    hunk_from_modified_pos(from_modif_pos){}

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

/* CONCRETE TOKENS: */
TokensGit::TokensGit() : Tokens::Tokens("^diff --git a/([^ ]+) b/.*$",
                                        1,
                                        "^@@ -([0-9]+),.* \\+([0-9]+),.*$",
                                        1, 2,
                                        "^ .*$",
                                        "^\\+.*$",
                                        "^-.*$"){}

TokensSvn::TokensSvn() : Tokens::Tokens("^Index: ([^ ]+).*$",
                                        1,
                                        "^@@ -([0-9]+),.* \\+([0-9]+),.*$",
                                        1, 2,
                                        "^ .*$",
                                        "^\\+.*$",
                                        "^-.*$"){}
