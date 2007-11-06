#include "tokens.h"
using std::string;

Tokens *factory(string type)
{
    Tokens *ret;

    ret = new TokensGit();
    DBG("factory(" << type << ") - ret: " << (long)ret);
    return ret;
}


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

/* CONCRETE TOKENS: */
TokensGit::TokensGit() : Tokens::Tokens("^diff --git a/([^ ]+) b/.*$",
                                        "^@@ -([0-9]+),.* \\+([0-9]+),.*$",
                                        "^ .*$",
                                        "^\\+.*$",
                                        "^-.*$"){}
