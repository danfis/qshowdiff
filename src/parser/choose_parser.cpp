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


Parser *chooseParser(In &in)
{
    // TODO: change type to int
    string type;
    QString line;

    in.startBuff();

    line = in.line();
    while (!line.isNull() && type.size() == 0){
        if (git.exactMatch(line))
            type = "git";

        if (bzr.exactMatch(line))
            type = "bzr";

        if (svn.exactMatch(line))
            type = "svn";

        if (diffr.exactMatch(line))
            type = "diffr";

        line = in.line();
    }

    in.endBuff();

    if (type == "git"){
        MSG("Chosen type: 'git'");
        return new ParserGit(in);
    }else if (type == "bzr"){
        MSG("Chosen type: 'bzr'");
        return new ParserBzr(in);
    }else if (type == "svn"){
        MSG("Chosen type: 'svn'");
        return new ParserSvn(in);
    }else if (type == "diffr"){
        MSG("Chosen type: 'diffr'");
        return new ParserDiffR(in);
    }
    return 0;
}

