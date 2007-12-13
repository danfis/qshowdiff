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

    filename_pos(filename_pos),
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
