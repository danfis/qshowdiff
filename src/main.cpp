#include <iostream>
#include <QApplication>
#include <unistd.h>

#include "diff/diff.h"
#include "diff/text.h"
#include "qt/main_window.h"
#include "settings.h"
#include "parser/parser.h"

using std::string;


int main(int argc, char *argv[])
{
    MILESTONE("");
    MILESTONE("====== START QSHOWDIFF ======");

    string input_type;

    if (argc != 2){
        std::cerr << "Error: At least one argument must be given." << std::endl;
        return 1;
    }

    input_type = argv[1];

    try{
        Parser parser(input_type, new QTextStream(stdin));
        parser.parse();
    }catch(ParserException &e){
        std::cerr << "Error: Parser can't parse this type of input." << std::endl;
        return 1;
    }

    DBG("Detaching from console.");
    if (daemon(0,0) != 0){
        std::cerr << "Error: Detaching failed. Proceeding without "
                     "detaching." << std::endl;
    }

	QApplication app(argc, argv);

	MainWindow win;
	win.show();
	app.exec();

    MILESTONE("====== FINISH QSHOWDIFF ======");
    MILESTONE("");
}
