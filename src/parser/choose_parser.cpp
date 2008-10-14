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
#include "parser/parser_diff.hpp"

static QRegExp git("^diff --git.*$");
static QRegExp bzr("^=== (added|removed|modified) file .*$");
static QRegExp svn("^Index: [^ ]+.*$");
static QRegExp diffr("^diff -r[a-zA-Z]* .*$");
static QRegExp diff("^[0-9]+(,[0-9]*)?[a-z][0-9]+(,[0-9])?$");

enum Type {
    NONE = -1,
    GIT = 0,
    BZR = 1,
    SVN = 2,
    DIFFR = 3,
    DIFF = 4,
    NUM_TYPES
};

const char *types[] = {
    "git",
    "bzr",
    "svn",
    "diffr",
    "diff"
};
int types_len = sizeof(types) / sizeof(const char *);

/**
 * Mapping between Type and name of type.
 */
struct TypesMapping {
    Type type;
    const char *name;
} types_map[] = {
    { GIT, "git" },
    { BZR, "bzr" },
    { BZR, "bazaar" },
    { SVN, "svn" },
    { SVN, "subversion" },
    { DIFFR, "diffr" },
    { DIFF, "diff" },
};

/**
 * Length of array types_map - statically initialized.
 */
int types_map_len = sizeof(types_map) / sizeof(const char *);



static Parser *parser(In &in, Type);


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

        if (diff.exactMatch(line))
            type = DIFF;

        line = in.line();
    }

    in.endBuff();

    return parser(in, type);
}

Parser *chooseParser(In &in, const char *type)
{
    for (int i=0; i < types_map_len; i++){
        if (strcasecmp(type, types_map[i].name) == 0){
            return parser(in, types_map[i].type);
        }
    }
    return 0;
}

Parser *parser(In &in, Type type)
{
    if (type >= 0 && type < NUM_TYPES){
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
        case DIFF:
            return new ParserDiff(in);
        default:
            return 0;
    }
}

