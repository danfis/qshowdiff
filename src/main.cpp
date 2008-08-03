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

#include <iostream>
#include <QApplication>
#include <unistd.h>

#include "diff/diff.h"
#include "diff/text.h"
#include "qt/main_window.h"
#include "settings.h"
#include "parser/parser.h"

using std::string;

#ifndef DEFAULT_TYPE
# define DEFAULT_TYPE "git"
#endif

void usage(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    MILESTONE("");
    MILESTONE("====== START QSHOWDIFF ======");

    string input_type;

    if (argc == 1){
        input_type = DEFAULT_TYPE;
    }else if (argc == 2){
        input_type = argv[1];
    }else{
        usage(argc, argv);
        return -1;
    }

    try{
        Parser parser(input_type, new QTextStream(stdin));
        parser.parse();
    }catch(ParserException &e){
        std::cerr << "Error: Unknown type of input." << std::endl;
        usage(argc, argv);
        return -1;
    }

    DBG("Detaching from console.");
    if (daemon(0,0) != 0){
        std::cerr << "Error: Detaching failed. Proceeding without "
                     "detaching." << std::endl;
    }

    QApplication app(argc, argv);

    MainWindow win;
    win.show();
    win.grabKeyboard();
    app.exec();

    MILESTONE("====== FINISH QSHOWDIFF ======");
    MILESTONE("");
}

void usage(int argc, char *argv[])
{
    std::string def(DEFAULT_TYPE);

    std::cerr << "Usage: " << argv[0] << " [ type ]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "  Types can be:" << std::endl;

    for (int i=0; all_tokens[i].name != 0; i++){
        std::cerr << "      " << all_tokens[i].name;
        if (def.compare(all_tokens[i].name) == 0)
            std::cerr << " (default)";
        std::cerr << std::endl;
    }
}

