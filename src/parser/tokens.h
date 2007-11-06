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

class TokensSvn : public Tokens{
  public:
    TokensSvn();
};

Tokens *TokenFactory(std::string);
#endif
