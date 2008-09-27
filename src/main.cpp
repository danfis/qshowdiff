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
#include <QTextCodec>
#include <QList>
#include <QByteArray>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#include "msg.hpp"
#include "settings.hpp"

#include "diff/diff.hpp"
#include "diff/text.hpp"

#include "qt/main_window.hpp"

#include "parser/parser.hpp"
#include "parser/in.hpp"
#include "parser/choose_parser.hpp"

using std::string;

#ifndef DEFAULT_TYPE
# define DEFAULT_TYPE "git"
#endif

void usage(int argc, char *argv[]);
char *codecPart(char *str);
void availableCodecs();

enum options_enum {
    HELP = 'h',
    TEXT_CODEC,
    AVAILABLE_CODECS
};

static struct option options[] = {
    { "help", no_argument, NULL, HELP },

    { "text-codec", required_argument, NULL, TEXT_CODEC },
    { "available-codecs", no_argument, NULL, AVAILABLE_CODECS },
    { NULL, 0, NULL, 0}
};

int main(int argc, char *argv[])
{
    int c, option_index;
    QTextCodec *codec = 0;
    string input_type;

    MILESTONE("");
    MILESTONE("====== START QSHOWDIFF ======");

    // OPTIONS:
    while ((c = getopt_long(argc, argv, "h", options, &option_index)) != -1){
        switch (c){
            case HELP:
                usage(argc, argv);
                return -1;
                break;
            case TEXT_CODEC:
                codec = QTextCodec::codecForName(optarg);
                if (codec == 0){
                    ERROR("Uknown text codec: '" << (char *)optarg << "'");
                    usage(argc, argv);
                    return -1;
                }
                break;
            case AVAILABLE_CODECS:
                availableCodecs();
                return -1;
            default:
                usage(argc, argv);
                return -1;
        }
    }

    if (codec == 0){
#ifdef DEFAULT_CODEC
        /* Set up codec manualy */
        codec = QTextCodec::codecForName(DEFAULT_CODEC);
#else /* DEFAULT_CODEC */
        char *var = NULL;

        var = getenv("LC_ALL");
        if (var == NULL || strlen(var) <= 0)
            var = getenv("LC_CTYPE");
        if (var == NULL || strlen(var) <= 0)
            var = getenv("LANG");

        if (var != NULL){
            var = codecPart(var);
            codec = QTextCodec::codecForName(var);

            DBG("Detected codec: '" << var << "'");
        }

        if (codec == 0){
            DBG("Previously detected codec wasn't accepted. Falling to codecForLocale.");
            codec = QTextCodec::codecForLocale();
        }
    }
#endif /* DEFAULT_CODEC */

    DBG("Codec: " << (const char *)codec->name());
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    if (argc - optind == 0){
        input_type = DEFAULT_TYPE;
    }else if (argc - optind == 1){
        input_type = argv[optind];
    }else{
        usage(argc, argv);
        return -1;
    }

    In in(stdin);
    Parser *parser = chooseParser(in);
    if (parser != 0){
        parser->parse();
        delete parser;
    }else{
        std::cerr << "Error: Unknown type of input." << std::endl;
        usage(argc, argv);
        return -1;
    }

#ifdef NDEBUG
    DBG("Detaching from console.");
    if (daemon(0,0) != 0){
        std::cerr << "Error: Detaching failed. Proceeding without "
                     "detaching." << std::endl;
    }
#endif

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

    std::cerr << "Usage: " << argv[0] << "  [ OPTIONS ]  type" << std::endl;
    std::cerr << std::endl;
    std::cerr << "  OPTIONS:" << std::endl;
    std::cerr << "      --text-codec  codec_name  Specify which text codec will be used during reading diff" << std::endl;
    std::cerr << "                                Available codecs can be found using option --available-codec" << std::endl;
    std::cerr << "      --available-codecs  Print out all available codecs" << std::endl;

    std::cerr << std::endl;
    std::cerr << "  Types can be:" << std::endl;

    /*
       TODO
    for (int i=0; all_tokens[i].name != 0; i++){
        std::cerr << "      " << all_tokens[i].name;
        if (def.compare(all_tokens[i].name) == 0)
            std::cerr << " (default)";
        std::cerr << std::endl;
    }
    */
}

char *codecPart(char *str)
{
    char *c;

    c = str;
    while (*c != 0 && *c != '.')
        c++;
    if (*c == '.' && *++c != 0){
        return c;
    }else{
        return str;
    }
}

void availableCodecs()
{
    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    QList<QByteArray>::iterator it, it_end;

    std::cerr << "Available codecs are:" << std::endl;
    it = codecs.begin();
    it_end = codecs.end();
    for (; it != it_end; ++it)
        std::cerr << "    " << (const char *)*it << std::endl;
    std::cerr << std::endl;
}
