#include <QApplication>

#include "diff/file.h"
#include "diff/text.h"
#include "qt/main_window.h"


File *createFile()
{
    File *file = new File("filename");
    Hunk *h1 = new Hunk(100, 105);
    Hunk *h2 = new Hunk(150, 155);
    Hunk *h3 = new Hunk(250, 255);
    Text *t1 = new Text();
    Text *t2 = new Text();
    Text *t3 = new Text();
    Text *t4 = new Text();

    t1->addLine(new QString("Line1"));
    t1->addLine(new QString("Line2"));
    t1->addLine(new QString("Line3"));
    t2->addLine(new QString("LLine3"));
    t2->addLine(new QString("LLine3"));
    t2->addLine(new QString("LLine3"));
    t3->addLine(new QString("LLLine3"));
    t3->addLine(new QString("LLLine3"));
    t3->addLine(new QString("LLLine3"));
    t4->addLine(new QString("LLLLine3"));
    t4->addLine(new QString("LLLLLine3"));

    h1->addSnippet(new Context(new Text(*t1)));
    h1->addSnippet(new Added(new Text(*t2)));
    h1->addSnippet(new Context(new Text(*t1)));

    h2->addSnippet(new Deleted(new Text(*t3)));
    h2->addSnippet(new Context(new Text(*t1)));

    h3->addSnippet(new Changed(new Text(*t4), new Text(*t3)));
    h3->addSnippet(new Added(new Text(*t1)));
    h3->addSnippet(new Context(new Text(*t2)));

    file->addHunk(h1);
    file->addHunk(h2);
    file->addHunk(h3);

    delete t1;
    delete t2;
    delete t3;
    delete t4;

    return file;
}

int main(int argc, char *argv[])
{
    File *file = createFile();

	QApplication app(argc, argv);
	MainWindow win;
	win.show();
	app.exec();
    delete file;
}
