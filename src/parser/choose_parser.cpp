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

#include <string>
using namespace std;

#include <QRegExp>

#include "parser/choose_parser.hpp"
#include "parser/parser_git.hpp"
#include "parser/parser_svn.hpp"
#include "parser/parser_bzr.hpp"
#include "parser/parser_diffr.hpp"

static QRegExp git("^diff --git.*$");
static QRegExp bzr("^=== (added|removed|modified) file .*$");
static QRegExp svn("^Index: [^ ]+.*$");
static QRegExp diffr("^diff -r[a-zA-Z]* .*$");

enum Type {
    NONE = -1,
    GIT = 0,
    BZR,
    SVN,
    DIFFR,
    NUM_TYPES
};

const char *types[] = {
    "git",
    "bzr",
    "svn",
    "diffr"
};


Parser *chooseParser(In &in)
{
    Type type = NONE;
    QString line;

    in.startBuff();

    line = in.line();
    while (!line.isNull() && type == NONE){
        if (git.exactMatch(line))
            type = GIT;

        if (bzr.exactMatch(line))
            type = BZR;

        if (svn.exactMatch(line))
            type = SVN;

        if (diffr.exactMatch(line))
            type = DIFFR;

        line = in.line();
    }

    in.endBuff();

    if (type != NONE){
        MSG("Chosen type '" << types[type] << "'");
    }

    switch (type){
        case GIT:
            return new ParserGit(in);
        case BZR:
            return new ParserBzr(in);
        case SVN:
            return new ParserSvn(in);
        case DIFFR:
            return new ParserDiffR(in);
        default:
            return 0;
    }
}

Parser *chooseParser(In &in, const char *type)
{
    if (strcasecmp(type, "git") == 0){
        MSG("Chosen type '" << types[GIT] << "'");
        return new ParserGit(in);
    }else if (strcasecmp(type, "bzr") == 0){
        MSG("Chosen type '" << types[BZR] << "'");
        return new ParserBzr(in);
    }else if (strcasecmp(type, "svn") == 0){
        MSG("Chosen type '" << types[SVN] << "'");
        return new ParserSvn(in);
    }else if (strcasecmp(type, "diffr") == 0){
        MSG("Chosen type '" << types[DIFFR] << "'");
        return new ParserDiffR(in);
    }

    return 0;
}

