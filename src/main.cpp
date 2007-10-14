#include <QApplication>

#include "diff/diff.h"
#include "diff/text.h"
#include "qt/main_window.h"
#include "settings.h"
#include "parser/parser.h"


int main(int argc, char *argv[])
{
    MILESTONE("");
    MILESTONE("====== START QSHOWDIFF ======");

    Parser parser("git", new QTextStream(stdin));
    parser.parse();

	QApplication app(argc, argv);

	MainWindow win;
	win.show();
	app.exec();

    MILESTONE("====== FINISH QSHOWDIFF ======");
    MILESTONE("");
}
