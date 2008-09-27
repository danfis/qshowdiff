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

#ifndef _PARSER_DIFFR_HPP_
#define _PARSER_DIFFR_HPP_

#include "parser/parser_big.hpp"

class ParserDiffR : public ParserBig {
  public:
    ParserDiffR(In &in)
        : ParserBig(in,
                "^diff -r[a-zA-Z]* ([^ ]+ [^ ]+).*$",
                "^([0-9]+)(,[0-9]+){0,1}[a-zA-Z]?([0-9]+)(,[0-9]+){0,1}.*$",
                "^ .*$",
                "^>.*$",
                "^<.*$"){}
};

#endif


