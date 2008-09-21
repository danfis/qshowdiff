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

/**
 * In this file are placed all macros and stuff for debuging,
 */
#ifndef _MSG_HPP_
#define _MSG_HPP_

#include <iostream>

#define MSG(msg) \
    std::cerr << msg << std::endl

#define DEBUG_HELPER(msg, type) \
    std::cerr << type << ": " << msg << std::endl; \
    std::cerr.flush()

#define ERROR(msg) DEBUG_HELPER(msg, "Error")

/**
 * TODO: Colored output
 * DBG("error" << "message");
 * ERROR("error" << "message");
 */
#ifndef NDEBUG
    #define DBG(msg) DEBUG_HELPER(msg, "Debug")
    #define WARNING(msg) DEBUG_HELPER(msg, "Warning")
    #define MILESTONE(msg) DEBUG_HELPER(msg, "Milestone")
#else
    #define DBG(msg)
    #define WARNING(msg, type)
    #define MILESTONE(msg)
#endif

#endif
